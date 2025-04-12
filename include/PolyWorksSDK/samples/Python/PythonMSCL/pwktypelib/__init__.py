from collections import namedtuple
import comtypes.client
import os
import util
import winreg

""" This module contains various functions related to loading Polyworks COM type lib
"""

RegInfo = namedtuple('RegInfo', ['cls_id', 'path'])


def get_info_from_reg(module):
    """ Return path from module name

    :param module: module name  (e.g. InnovMetric.PolyWorks.WorkspaceManager --> CLSID --> LocalServer32)
    :return: clsid and module path
    """
    with winreg.ConnectRegistry(None, winreg.HKEY_CLASSES_ROOT) as key_cls_root:
        with winreg.OpenKey(key_cls_root, r"{0}\CLSID".format(module), 0, winreg.KEY_READ | winreg.KEY_WOW64_64KEY) as key_cls_id:
            cls_id = winreg.QueryValue(key_cls_id, "")
        with winreg.OpenKey(key_cls_root, r"CLSID\{0}\LocalServer32".format(cls_id), 0, winreg.KEY_READ | winreg.KEY_WOW64_64KEY) as key_path:
            path = winreg.QueryValue(key_path, "")
        return RegInfo(cls_id, path.strip('"'))


def get_type_lib(module_name):
    """ Create and return module for the following modules

    module possible values are :
          WorkspaceManager
          IMInspect
          IMEdit
          IMView
          IMAlign
    :param module_name: name of the module type
    :return: type lib for module type
    """
    module_name = util.format_module_name(module_name)
    info = get_info_from_reg(util.format_prog_id(module_name))
    try:
        return comtypes.client.GetModule(info.path)
    except FileNotFoundError:
        # Bug in comtypes version 1.0.1
        # Type lib is stored as a property of executable of module
        # and can't be found by os.path in comtypes\tools\codegenerator
        # workaround is calling comtypes.client.GetModule(info.path) again to generate all files properly
        try:
            return comtypes.client.GetModule(info.path)
            
        except FileNotFoundError:
            pass

def get_module(module_name):
    """ Get module

    :param module_name: name of the module type
    :return: module
    """
    type_lib = get_type_lib(module_name)
    itf = None
    if module_name.lower() == util.EModuleNames.WORKSPACE_MANAGER.lower():
        itf = type_lib.IMWorkspaceManager
    elif module_name.lower() == util.EModuleNames.IMINSPECT.lower():
        itf = type_lib.IMInspect
    elif module_name.lower() == util.EModuleNames.IMEDIT.lower():
        itf = type_lib.IMEdit
    elif module_name.lower() == util.EModuleNames.IMVIEW.lower():
        itf = type_lib.IMView
    elif module_name.lower() == util.EModuleNames.IMALIGN.lower():
        itf = type_lib.IMAlign
    if itf is not None:
        return comtypes.client.CreateObject(itf)
    raise RuntimeError(f'typelib has no COM interface for {module_name}')
