import os
import psutil

"""
Addition functions
"""


def program_running(path):
    """ Check if a program is running

    :param path: path of an .exe
    :return: true if program is runing, false otherwise
    """
    program_id = os.path.basename(path)
    progs ={program.name().lower() for program in psutil.process_iter()}
    return program_id.lower() in progs


class EModuleNames:
    """ Class that regroups prog id

    """
    IMALIGN = "IMAlign"
    IMEDIT = "IMEdit"
    IMINSPECT = "IMInspect"
    IMVIEW = "IMView"
    WORKSPACE_MANAGER = "WorkspaceManager"
    supported_value = {IMALIGN, IMEDIT, IMINSPECT, IMVIEW, WORKSPACE_MANAGER}


def format_module_name(module_name):
    try:
        return next(name for name in EModuleNames.supported_value if module_name.lower() == name.lower())
    except StopIteration:
        raise NotImplementedError(f"{module_name}")


def format_prog_id(module_name):
    """ Format a string to match the prog_id format in register

    :param module_name: name of module
    :return: formatted string
    """
    return f"InnovMetric.PolyWorks.{module_name}"
