from contextlib import contextmanager
from ctypes import windll, POINTER, Structure
from ctypes.wintypes import HTASK, DWORD, WORD
from enum import IntEnum
from util import EModuleNames
import comtypes
import logging
import mscl
import os
import pythoncom
import workspacemanager

""" This module provide an API to facilitate calling various methods to execute MSCL commands and script
via IIMCommandCenter COM interface on a supported PolyWorks module
"""

logger = logging.getLogger(__name__)
retry_time_in_ms = 200


class tagINTERFACEINFO(Structure):
    pass


tagINTERFACEINFO._fields_ = [
    ('punk', POINTER(comtypes.IUnknown)),
    ('iid', comtypes.GUID),
    ('wMethod', WORD)]


class PENDINGMSG(IntEnum):
    PENDINGMSG_CANCELCALL = 0
    PENDINGMSG_WAITNOPROCESS = 1
    PENDINGMSG_WAITDEFPROCESS = 2


class SERVERCALL(IntEnum):
    SERVERCALL_ISHANDLED = 0
    SERVERCALL_REJECTED = 1
    SERVERCALL_RETRYLATER = 2


class CALLTYPE(IntEnum):
    CALLTYPE_TOPLEVEL = 1
    CALLTYPE_NESTED = 2
    CALLTYPE_ASYNC = 3
    CALLTYPE_TOPLEVEL_CALLPENDING = 4
    CALLTYPE_ASYNC_CALLPENDING = 5


class IMessageFilter(comtypes.IUnknown):
    """ IMessageFilter COM interface """
    _iid_ = comtypes.GUID('{00000016-0000-0000-C000-000000000046}')
    _idlflags_ = []


IMessageFilter._methods_ = [
    comtypes.COMMETHOD([], DWORD, 'HandleInComingCall',
                       (['in'], DWORD, 'dwCallType'), (['in'], HTASK, 'htaskCaller'), (['in'], DWORD, 'dwTickCount'),
                       (['in', 'optional'], POINTER(tagINTERFACEINFO), 'lpInterfaceInfo')),
    comtypes.COMMETHOD([], DWORD, 'RetryRejectedCall',
                       (['in'], HTASK, 'htaskCallee'),
                       (['in'], DWORD, 'dwTickCount'),
                       (['in'], DWORD, 'dwRejectType')),
    comtypes.COMMETHOD([], DWORD, 'MessagePending',
                       (['in'], HTASK, 'htaskCallee'),
                       (['in'], DWORD, 'dwTickCount'),
                       (['in'], DWORD, 'dwPendingType'))]


class ComMessageFilter(comtypes.COMObject):
    _com_interfaces_ = [IMessageFilter]

    def __init__(self):
        pass

    def HandleInComingCall(self, this, dwCallType, htaskCaller, dwTickCount, lpInterfaceInfo):
        if dwCallType == CALLTYPE.CALLTYPE_TOPLEVEL_CALLPENDING:
            return SERVERCALL.SERVERCALL_RETRYLATER
        return SERVERCALL.SERVERCALL_ISHANDLED

    def RetryRejectedCall(self, this, htaskCallee, dwTickCount, dwRejectType):
        if dwRejectType == SERVERCALL.SERVERCALL_RETRYLATER:
            return retry_time_in_ms
        return DWORD(-1)

    def MessagePending(self, this, htaskCallee, dwTickCount, dwPendingType):
        return PENDINGMSG.PENDINGMSG_WAITDEFPROCESS


@contextmanager
def com_context():
    """  context for a single-thread apartment model process """
    try:
        # Create and release the COM library for the calling thread
        pythoncom.CoInitializeEx(pythoncom.COINIT_APARTMENTTHREADED)
        # Create and release the message filter to fix 'Application is busy', 'Call was Rejected By Callee' from client
        ole32 = windll.LoadLibrary("ole32.dll")
        com_filter = ComMessageFilter()
        p = com_filter.QueryInterface(IMessageFilter)
        res = None
        if ole32 is not None and p is not None:
            res = ole32.CoRegisterMessageFilter(p, None)
        yield
    finally:
        if ole32 is not None and res is not None:
            ole32.CoRegisterMessageFilter(None, None)
        pythoncom.CoUninitialize()


class CommandCenterWrapper:

    @classmethod
    def from_module(cls, module_name, project_name=None):
        """ Create and return CommandCenter for the following modules

        module_name possible values are :
              WorkspaceManager
              IMInspect
              IMEdit
              IMView
              IMAlign
        :param module_name: module name
        :param project_name: running .pwk name
        :return: CommandCenterWrapper
        """
        wm = workspacemanager.WorkspaceManagerWrapper.from_module(module_name)
        if module_name.lower() == EModuleNames.WORKSPACE_MANAGER.lower():
            return cls(wm.create_command_center())
        command_centers = wm.get_command_centers_of_running_module()
        if len(command_centers) == 0:
            raise RuntimeError(f"Failed to create Command center for requested module name {module_name}")
        if project_name is not None:
            try:
                command_center = next(
                    command_center for name, command_center in command_centers if name == project_name)
                return cls(command_center)
            except StopIteration:
                return RuntimeError(f"{project_name} is not available in {module_name}")
        # if no project is specified, we return a command center for the first
        return cls(command_centers[0][1])

    def __init__(self, command_center):
        """ This class wrap IIMCommandCenter function in python

        :param command_center: pointer to IIMCommandCenter
        """
        self.command_center = command_center

    def execute_command_script(self, command_info):
        """ Execute a MSCL command with [out] parameter and extracts the results

        :param command_info: MSCLCommand
        :return: [out] parameters of MSCL command
        """
        script = mscl.generate_command_get_script(command_info)
        res = self.has_succeeded(self.command_center.ScriptExecuteFromBuffer(script, ""))
        logger.debug(f"{command_info.command} succeeded {res}")

        # Extract values after script execution
        number_of_expected_parameter_out = len(command_info.variables_out)
        if number_of_expected_parameter_out == 1:
            if not res:
                return None
            return self.extract_values_after_execution(command_info.variables_out[0])
        else:
            if not res:
                res = tuple(None for _i in range(number_of_expected_parameter_out))
                return res
            return tuple(self.extract_values_after_execution(variable) for variable in command_info.variables_out)

    def execute_command(self, command, *args):
        """ Execute a MSCL command on a valid IIMCommandCenter

        ex : TREEVIEW POLYGONAL_MODEL PROPERTIES DISPLAY COLOR GET( r, g, b, "file.pol" )
             command= TREEVIEW POLYGONAL_MODEL PROPERTIES DISPLAY COLOR GET
                args= mscl.Out, mscl.Out, mscl.Out, "file.pol"
        :param command: MSCL command
        :param args: additional arguments to be added from left to right
        :return: success of the operation
        """
        command_info = mscl.MSCLCommand(command, *args)
        if len(command_info.variables_out) > 0:
            return self.execute_command_script(command_info)
        elif not args:
            return self.command_center.CommandExecute(command) == 0
        else:
            return self.command_center.CommandExecute(command_info.command) == 0

    def execute_get_command(self, command_str):
        """ Execute a MSCL command on a valid IIMCommandCenter

         ex : TREEVIEW POLYGONAL_MODEL PROPERTIES DISPLAY COLOR GET( r, g, b, "file.pol" )
         command should be "TREEVIEW POLYGONAL_MODEL PROPERTIES DISPLAY COLOR GET( , , ,"file.pol")"
         because r,g,b parameter [out]

        :param command_str: MSCL command string
        :return: [out] parameters of MSCL command
        """
        return self.execute_command_script(mscl.parse_command_get_str(command_str))

    def execute_script_from_file(self, path, *args):
        """ Execute a MSCL script

        :param path: path to a .pwmacro
        :param args: script arguments
        :return: success of the operation
        """
        with open(path, 'r') as file:
            res = self.command_center.ScriptExecuteFromBuffer(file.read(), mscl.format_args_for_script(*args))
            logger.debug(f"{os.path.basename(path)} succeeded {self.has_succeeded(res)}")

    def extract_values_after_execution(self, variable_name):
        """ Get the value of a variable from the last executed MSCL script

        :param variable_name: name of script variable
        :return: list of values
        """
        num_values = self.command_center.ScriptVariableGetNbValues(variable_name)
        if num_values == 1:
            value = self.command_center.ScriptVariableGetValueAsString(variable_name, 1)
            return mscl.parse_variable_value(value[0]) if self.has_succeeded(value[1]) else None
        else:
            values = [self.command_center.ScriptVariableGetValueAsString(variable_name, i)
                      for i in range(1, num_values)]
            return [mscl.parse_variable_value(value[0]) if self.has_succeeded(value[1]) else None for value in values]

    def get_shared_variable_value(self, name):
        """ Get the value of a shared variable

        :param name: name of the shared variable
        :return: value of rhe shared variable
        """
        return self.execute_command("MACRO SHARED_VARIABLE GET_VALUE", name, mscl.Out())

    def has_succeeded(self, code):
        """ Return success of last executed command

        :return: success of the operation
        """
        success = self.command_center.ReturnValueIsSuccess(code)
        return success == 1

    def set_shared_variable_value(self, name, value):
        """ Set the value of a shared variable

        :param name: name of the shared variable
        :param value: value of rhe shared variable
        :return: success of the operation
        """
        if self.get_shared_variable_value(name) is not None:
            res = self.command_center.CommandExecute(
                f"MACRO SHARED_VARIABLE SET_VALUE({mscl.format_arg(name)}, {mscl.format_arg(value)})")
        else:
            res = self.command_center.CommandExecute(
                f"MACRO SHARED_VARIABLE CREATE({mscl.format_arg(name)}, {mscl.format_arg(value)})")
        return self.has_succeeded(res)
