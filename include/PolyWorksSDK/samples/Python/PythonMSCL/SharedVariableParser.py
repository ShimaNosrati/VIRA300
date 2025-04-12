# -*- coding: UTF-8 -*-
from pwktypelib import get_type_lib
from workspacemanager import WorkspaceManagerWrapper
import argparse
import commandcenter
import logging

"""
Main for PolyWorks sdk python sample
This sample shows basic manipulations on PolyWorks modules
"""

logger = logging.getLogger(__name__)


def processing(variable):
    """
    TO REPLACE
    dummy python processing, for now we only print the shared variable
    :return:
    """
    variable_type = type(variable)
    logger.debug(f"{variable} is a {variable_type}")
    return "New value"


def configure_log(log_level):
    """ Set log level (only debug is implemented)

    :param log_level name: of the module
    """
    logging.basicConfig(level=log_level)
    logging.getLogger('comtypes').setLevel(logging.WARNING)


def load_type_lib(module_name_ls):
    """ Generates code in comtypes\gen for typelib

    :param module_name_ls: name of the module
    """
    for module_name in module_name_ls:
        get_type_lib(module_name)


def main(shared_variable_ls):
    """
    This sample process values and store them in shared variable
    :return:
    """
    with commandcenter.com_context():
        # 1. Get a workspace manager
        wm = WorkspaceManagerWrapper.from_module("iminspect")
        wm_cmd_center = commandcenter.CommandCenterWrapper(wm.create_command_center())
        
        # 2. Get shared variables and change their values
        for variable_name in shared_variable_ls:
            value = wm_cmd_center.get_shared_variable_value(variable_name)
            logger.debug(f"shared variable {variable_name} is {value}")
            new_value = processing(value)
            res = wm_cmd_center.set_shared_variable_value(variable_name, new_value)
            logger.debug(f"setting shared variable {variable_name} to {new_value} ... {res}")
        

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--m", "--modules", nargs="+", dest="module_name_ls")
    parser.add_argument("--v", "--vars", nargs="+", dest="shared_variable_ls")
    logging_choices = ['CRITICAL', 'FATAL', 'ERROR', 'WARN', 'INFO', 'DEBUG']
    parser.add_argument("-l", "--logging", dest="log_level", default='WARNING', choices=logging_choices)
    args = parser.parse_args()
    configure_log(args.log_level)
    if args.module_name_ls:
        load_type_lib(args.module_name_ls)
    elif args.shared_variable_ls:
        main(args.shared_variable_ls)
