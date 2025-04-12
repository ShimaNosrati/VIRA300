# -*- coding: UTF-8 -*-
import argparse
import commandcenter
import logging
from pwktypelib import get_type_lib
from mscl import Out as outParam
import workspacemanager

"""
Main for PolyWorks sdk python sample
This sample shows basic manipulations on PolyWorks modules
"""

logger = logging.getLogger(__name__)


def load_type_lib(module_name_ls):
    """ Generates code in comtypes\gen for typelib

    :param module_name_ls: name of the module
    """
    for module_name in module_name_ls:
        get_type_lib(module_name)


def configure_log(log_level):
    """ Set log level (only debug is implemented)

    :param log_level name of the module
    """
    logging.basicConfig(level=log_level)
    logging.getLogger('comtypes').setLevel(logging.WARNING)


def main(use_running_inspector_module):
    """ This sample is an example of shared variable manipulation

    :param use_running_inspector_module name of the module
    """
    with commandcenter.com_context():
        # 1. Get command center for PolyWorks|Inspector
        wm = workspacemanager.WorkspaceManagerWrapper.from_module("IMInspect")
        inspector_list = wm.get_command_centers_of_running_module()
        if len(inspector_list) == 0 or not use_running_inspector_module:
            imi_cmd_center = commandcenter.CommandCenterWrapper(wm.create_command_center_from_module(wm.start_module()))
        else:
            _, p_command_center = inspector_list[0]
            imi_cmd_center = commandcenter.CommandCenterWrapper(p_command_center)
        
        # 2. Call a command for sanity
        test_command = "ECHO"
        # 42 should be seen in selected PolyWorks|Inspector's command history
        logger.debug(f"{test_command} succeeded { imi_cmd_center.execute_command(test_command, 42)}")
        
        # 3. Create features using python
        # 3.1 Create a plane
        plane_name = "plane 1"
        create_plane_command = "FEATURE PRIMITIVE PLANE CREATE FROM_POINT_AND_NORMAL"
        res = imi_cmd_center.execute_command(create_plane_command, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, "Nominal", plane_name, "",
                                             "", "")
        logger.debug(f"{create_plane_command} succeeded {res}")
        # 3.2 Create a cricle
        circle_name = "circle 1"
        create_circle_command = "FEATURE PRIMITIVE CIRCLE CREATE"
        res = imi_cmd_center.execute_command(create_circle_command, 2.0, 2.0, 0.0, 0.0, 0.0, 1.0, 1.0, "Nominal",
                                             circle_name, "")
        logger.debug(f"{create_circle_command} succeeded {res}")
        # 3.3 Check that 2 features were created
        number_of_feature = imi_cmd_center.execute_command("TREEVIEW FEATURE COUNT GET", outParam())
        logger.debug(f"TREEVIEW has {number_of_feature} features")
        
        # 4. Change feature properties
        nominal_plane_name = f"{plane_name} -nom-"
        change_plane_center_command = "TREEVIEW PRIMITIVE PLANE PROPERTIES POINT"
        res = imi_cmd_center.execute_command(change_plane_center_command, 5, 5, 0, nominal_plane_name)
        logger.debug(f"{change_plane_center_command} succeeded {res}")
        
        # 5. Get some feature informations from PolyWorks|Inspector
        # 5.1 Get some information about a feature plane
        x, y, z = imi_cmd_center.execute_command("TREEVIEW PRIMITIVE PLANE PROPERTIES POINT GET", outParam(),
                                                                      outParam(), outParam(), nominal_plane_name)
        A, B, C, D = imi_cmd_center.execute_command("TREEVIEW PRIMITIVE PLANE PROPERTIES EQUATION GET", outParam(),
                                                    outParam(), outParam(), outParam(), nominal_plane_name)
        i, j, k = imi_cmd_center.execute_command("TREEVIEW PRIMITIVE PLANE PROPERTIES NORMAL GET", outParam(), outParam(),
                                                 outParam(), nominal_plane_name)
        logger.debug(f"{plane_name}: origin ({x}, {y}, {z} - normal ({i}, {j}, {k}) of equation {A}x + {B}y + {C}z = {D})")
        # 5.2 Get some informations about a feature circle
        nominal_circle_name = f"{circle_name} -nom-"
        x, y, z = imi_cmd_center.execute_command("TREEVIEW PRIMITIVE CIRCLE PROPERTIES CENTER GET", outParam(),
                                                 outParam(), outParam(), nominal_circle_name)
        radius = imi_cmd_center.execute_command("TREEVIEW PRIMITIVE CIRCLE PROPERTIES RADIUS GET", outParam(),
                                                nominal_circle_name)
        i, j, k = imi_cmd_center.execute_command("TREEVIEW PRIMITIVE CIRCLE PROPERTIES AXIS_ORIENTATION GET", outParam(),
                                                 outParam(), outParam(), nominal_circle_name)
        logger.debug(f"{circle_name}: point ({x},{y},{z}) - radius: {radius} - normal ({i}, {j}, {k})")

    # 6. Close opened PolyWorks|Inspector module if needed
    file_exit_command = "FILE EXIT"
    res = imi_cmd_center.execute_command(file_exit_command)
    logger.debug(f"{file_exit_command} succeeded {res}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--m", "--modules", nargs="+", dest="module_name_ls")
    parser.add_argument("-s", "--start-module", dest="start_module")
    logging_choices = ['CRITICAL', 'FATAL', 'ERROR', 'WARN', 'INFO', 'DEBUG']
    parser.add_argument("-l", "--logging", dest="log_level", default='WARNING', choices=logging_choices)
    args = parser.parse_args()
    configure_log(args.log_level)
    if args.module_name_ls:
        load_type_lib(args.module_name_ls)
    else:
        main(args.start_module)
