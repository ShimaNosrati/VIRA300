# -*- coding: UTF-8 -*-
import argparse
import commandcenter
import logging
import os
import numpy as np
from pwktypelib import get_info_from_reg, get_type_lib
import util
import workspacemanager

"""
Main for PolyWorks sdk python sample
This sample shows basic manipulations on PolyWorks modules
"""

logger = logging.getLogger(__name__)


def processing():
    """ TO REPLACE

    dummy python processing
    """
    array = np.array([[1, 2, 3], [3, 2, 1], [1, 0, -1]])
    eigenvalues, v = np.linalg.eig(array)
    return np.around(np.min(eigenvalues), decimals=2)


def processing2():
    """TO REPLACE

    dummy python processing
    """
    a = np.array([[3, 7, 3], [1, 4, 2], [7, 2, 4]])
    b = np.array([1, 2, 3])
    res = np.linalg.solve(a, b)
    return np.around(np.max(res), decimals=2)


def load_type_lib(module_name):
    """ Generates code in comtypes\gen for typelib

    :param module_name name of the module
    """
    type_lib = get_type_lib(module_name)
    logging.debug(dir(type_lib))


def configure_log(log_level):
    """ Set log level (only debug is implemented)

    :param log_level name of the module
    """
    logging.basicConfig(level=log_level)
    logging.getLogger('comtypes').setLevel(logging.WARNING)


def main():
    """ This sample is an example of shared variable manipulation

    """
    with commandcenter.com_context():
        # 1. Get a workspace manager
        wm = workspacemanager.WorkspaceManagerWrapper.from_module("IMInspect")
        wm_cmd_center = commandcenter.CommandCenterWrapper(wm.create_command_center())
        # Call a command for sanity
        test_command = "ECHO"
        logger.debug(f"{test_command} succeeded { wm_cmd_center.execute_command(test_command, 42)}")
        
        # 2. Start inspector modules
        imi_cmd_center1 = commandcenter.CommandCenterWrapper(wm.create_command_center_from_module(wm.start_module()))
        imi_cmd_center2 = commandcenter.CommandCenterWrapper(wm.create_command_center_from_module(wm.start_module()))
        # Call a command for sanity
        logger.debug(f"{test_command} succeeded {imi_cmd_center1.execute_command(test_command, 42)}")
        logger.debug(f"{test_command} succeeded {imi_cmd_center2.execute_command(test_command, 42)}")
        
        # 3. Do some processing and store processing result in shared variable
        variable_1 = "variable_test_1"
        variable_2 = "variable_test_2"
        variable_3 = "variable_test_3"
        
        val_1 = 99.5
        val_2 = "shared_string_for_testing"
        val_3 = processing()
        
        res = wm_cmd_center.set_shared_variable_value(variable_1, val_1)
        res = wm_cmd_center.set_shared_variable_value(variable_2, val_2)
        res = wm_cmd_center.set_shared_variable_value(variable_3, val_3)
        
        logger.debug(f"Shared variable {variable_1} is {wm_cmd_center.get_shared_variable_value(variable_1)}")
        logger.debug(f"Shared variable {variable_2} is { wm_cmd_center.get_shared_variable_value(variable_2)}")
        logger.debug(f"Shared variable {variable_3} is {wm_cmd_center.get_shared_variable_value(variable_3)}")
        
        # 4. Call a .pwmacro script on inspector that modifies the shared variable
        script_path = os.path.join(os.getcwd(), "PythonCommand.pwmacro")
        if os.path.exists(script_path):
            imi_cmd_center1.execute_script_from_file(script_path, variable_1, "new value")
            imi_cmd_center2.execute_script_from_file(script_path, variable_2, -2)
            wm_cmd_center.execute_script_from_file(script_path, variable_3, processing2())
        
        # 5. Print the new shared variable values
        logger.debug(f"Shared variable {variable_1} is {wm_cmd_center.get_shared_variable_value(variable_1)}")
        logger.debug(f"Shared variable {variable_2} is { wm_cmd_center.get_shared_variable_value(variable_2)}")
        logger.debug(f"Shared variable {variable_3} is {wm_cmd_center.get_shared_variable_value(variable_3)}")
        
        # 6. Close opened PolyWorks|Inspector module if needed
        file_exit_command = "FILE EXIT"
        res = imi_cmd_center1.execute_command(file_exit_command)
        logger.debug(f"{file_exit_command} succeeded {res}")
        res = imi_cmd_center2.execute_command(file_exit_command)
        logger.debug(f"{file_exit_command} succeeded {res}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", "--name", dest="module_name")
    logging_choices = ['CRITICAL', 'FATAL', 'ERROR', 'WARN', 'INFO', 'DEBUG']
    parser.add_argument("-l", "--logging", dest="log_level", default='WARNING', choices=logging_choices)
    args = parser.parse_args()
    configure_log(args.log_level)
    if args.module_name:
        load_type_lib(args.module_name)
    else:
        main()
