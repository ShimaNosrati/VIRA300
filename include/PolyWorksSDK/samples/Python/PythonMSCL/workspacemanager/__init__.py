import pwktypelib
import util

"""
This module provides an API to facilitate 
calling various method on the IIMWorkspaceManager COM interface
"""


def get_module_com_interface(module_name):
    """ Get COM interface for a module

    module_name possible values are :
          IMInspect
          IMEdit
          IMView
          IMAlign
    if importing fails, load_type_lib must be run
    :param module_name: module name
    :return: COM interface and E_PW_MODULE_TYPE
    """
    try:
        pwktypelib.get_type_lib(module_name)
        pwktypelib.get_type_lib(util.EModuleNames.WORKSPACE_MANAGER)
        if module_name.lower() == util.EModuleNames.IMINSPECT.lower() \
                or module_name.lower() == util.EModuleNames.WORKSPACE_MANAGER.lower():
            from comtypes.gen.IMInspectLib import IIMInspect
            from comtypes.gen.IMWorkspaceManagerLib import E_PW_MODULE_TYPE_IMINSPECT
            return IIMInspect, E_PW_MODULE_TYPE_IMINSPECT
        elif module_name.lower() == util.EModuleNames.IMEDIT.lower():
            from comtypes.gen.IMEditLib import IIMEdit
            from comtypes.gen.IMWorkspaceManagerLib import E_PW_MODULE_TYPE_IMEDIT
            return IIMEdit, E_PW_MODULE_TYPE_IMEDIT
        elif module_name.lower() == util.EModuleNames.IMVIEW.lower():
            from comtypes.gen.IMViewLib import IIMView
            from comtypes.gen.IMWorkspaceManagerLib import E_PW_MODULE_TYPE_IMVIEW
            return IIMView, E_PW_MODULE_TYPE_IMVIEW
        elif module_name.lower() == util.EModuleNames.IMALIGN.lower():
            from comtypes.gen.IMAlignLib import IIMAlign
            from comtypes.gen.IMWorkspaceManagerLib import E_PW_MODULE_TYPE_IMALIGN
            return IIMAlign, E_PW_MODULE_TYPE_IMALIGN
    except ModuleNotFoundError:
        pass
    raise NotImplementedError(module_name)


class WorkspaceManagerWrapper:

    @classmethod
    def from_module(cls, module_name):
        """ Get WorkspaceManagerWrapper for a operation on a single module type

        module_name possible values are :
            IMInspect
            IMEdit
            IMView
            IMAlign
        :param module_name:  module name
        :return: WorkspaceManagerWrapper
        """
        wm = pwktypelib.get_module(util.EModuleNames.WORKSPACE_MANAGER)
        if wm is not None:
            interface, module_id = get_module_com_interface(module_name)
            return cls(wm, interface, module_id)
        raise RuntimeError("IIMWorkspaceManager2 pointer is unavailable")

    def __init__(self, wm, interface, module_id):
        """ This class encapsulates call to COM Interface IIMWorkspaceManager2

        :param wm: pointer to a IIMWorkspaceManager2
        :param interface: COM interface of module
        :param module_id: E_PW_MODULE_TYPE
        """
        self.wm = wm
        self.interface = interface
        self.module_id = module_id

    def create_command_center_from_module(self, p):
        """ Get command center from path and project name for a given module

        :param p: pointer to a module COM interface (IIMInspect)
        :return: tuple of project name and IIMCommandCenter
        """
        if p is None:
            return
        try:
            p = p.QueryInterface(self.interface)
        except Exception as e:
            raise RuntimeError("NULL COM pointer access")
            return
        if p is not None:
            p = p.ProjectGetCurrent()
        if p is not None:
            return p.CommandCenterCreate()
        raise RuntimeError("IIMCommandCenter is not supported by module")

    def create_command_center(self):
        """ Return command center for active IIMWorkspaceManager2

        :return: IIMCommandCenter
        """
        return self.wm.CommandCenterCreate()

    def get_all_projects_of_running_module(self):
        """ Get project names and paths of running modules of a given type

        (ex: all project currently open in running iminspect.exe)
        :return: list of project name and path
        """
        try:
            module_info_ls = self.wm.RunningModulesGet(self.module_id)
            return zip(list(module_info_ls[0]), list(module_info_ls[1]))
        except IndexError:
            # Throws an error if RunningModulesGet() is called when no program of module type
            #  (inspect, align, edit, etc.) is running
            return []

    def get_command_centers_of_running_module(self):
        """ Get all command centers of running modules of a given type

        (ex: all command centers for all opened PolyWorks|Inspector projects)
        :return: list of tuple of project name and IIMCommandCenter
        """
        return [(name, self.create_command_center_from_module(self.wm.ModuleGet(path, name)))
                for path, name in self.get_all_projects_of_running_module()]

    def start_module(self, name=None, path=None):
        """ Start a module

        :param name: name of a project of the module type
        :param path: Path of the workspace (Default to use the current workspace.)
        :return: pointer on the module
        """
        return self.wm.ModuleStart(self.module_id, path, name)


