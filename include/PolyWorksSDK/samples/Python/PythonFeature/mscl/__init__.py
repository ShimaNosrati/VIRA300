from collections import Iterable
import ast
import json
import re

"""
 This module converts type from MSCL to python
"""

_PARENTHESIS_REGEX = re.compile(r'\((.*?)\)')
_FLOAT_REGEX = re.compile(r'^-?\d?\.\d+$')

class Out:

    pass


class MSCLCommand:
    def __init__(self, command_word, *parameters):
        """ Constructor for MSCL command that encapsulates [out] parameters and formatted command string

        ex: TREEVIEW POLYGONAL_MODEL PROPERTIES DISPLAY COLOR GET( r, g, b, "file.pol" )
        command_word would be TREEVIEW POLYGONAL_MODEL PROPERTIES DISPLAY COLOR GET
        parameters would be Out, Out, Out, "file.pol"
        :param command_word: MSCL command string formatted without args
        :param parameters: Ierable containing command arguments
        """
        self.variables_out = []
        temp_ls = []
        for i, parameter in enumerate(parameters):
            if type(parameter) == Out:
                var_name_for_parameter_out = f"temporary_var_generated{i}"
                temp_ls.append(var_name_for_parameter_out)
                self.variables_out.append(var_name_for_parameter_out)
            else:
                temp_ls.append(format_arg(parameter))
        self.command = "{}({})".format(command_word, ','.join(temp_ls))


def is_float(var):
    return _FLOAT_REGEX.match(var) is not None


def parse_variable_value(variable_value_str):
    """ Parse MSCL executed command return string and generates a python type

    :param variable_value_str: a string or a list of string
    :return: a list of values
    """
    if variable_value_str is None:
        return variable_value_str
    elif isinstance(variable_value_str, str):
        if variable_value_str.isnumeric() or is_float(variable_value_str):
            return ast.literal_eval(variable_value_str)
        elif variable_value_str.lower() == 'on':
            return True
        elif variable_value_str.lower() == 'off':
            return False
        try:
            return json.loads(variable_value_str)
        except ValueError:
            return variable_value_str
    elif isinstance(variable_value_str, Iterable) and not isinstance(variable_value_str, dict):
        return [parse_variable_value(element) for element in variable_value_str]
    raise NotImplementedError(f'{type(variable_value_str)}')


def format_args_for_script(*args):
    """ Format arguments for MSCL script

    Whitespace are not supported in MSCL script arguments
    :param args: any number of arguments
    ex: args turtle, 3, -14.7, None become ""turtle" 3 -14.7"
    :return: formatted string containing arguments
    """
    return " ".join(format_arg(arg, True) for arg in args if arg)


def format_arg(var, remove_whitespace=False):
    """ Format string for MSCL to add " and remove whitespace if needed

    :param var: object
    :param remove_whitespace: flag to remove whitespace if needed
    :return: object with proper formatting
    """
    if isinstance(var, str):
        if var.isnumeric() or is_float(var):
            return var
        if not var:
            return var
        var = var.strip('"')
        if remove_whitespace:
            var = var.replace(" ", "")
        return f'"{var}"'
    if isinstance(var, Iterable) and not isinstance(var, dict):
        return '{{{}}}'.format(",".join(format_arg(element) for element in var))
    if var is None:
        return ""
    else:
        return str(var)


def generate_command_get_script(command_info):
    """ Generates a MSCL script to store the [out] variables

    :param command_info: MSCLCommand
    :return: MSCL script that executes an MSCL command
    """
    variable_declaration_str = "".join(f"DECLARE {variable}\n" for variable in command_info.variables_out)
    return f"version \"5.0\"\n{variable_declaration_str}{command_info.command}"


def parse_command_get_str(command):
    """ Extract parameters from a MSCL command Get string of form "COMMAND(arg1, arg2,...,argn)"

    ex : TREEVIEW POLYGONAL_MODEL PROPERTIES DISPLAY COLOR GET( r, g, b, "file.pol" )
         command should be "TREEVIEW POLYGONAL_MODEL PROPERTIES DISPLAY COLOR GET( , , ,"file.pol")"
         because r,g,b parameter [out]
    :param command: full MSCL command string with arg
    :return: command and list of parameter out
    """
    parameter_str = _PARENTHESIS_REGEX.findall(command)
    if len(parameter_str) <= 0:
        return MSCLCommand(command, Out())
    command_word = _PARENTHESIS_REGEX.sub("", command).strip("()").strip()
    command_parameter_tuple = (Out() if parameter.isspace() or parameter == "" else parameter.strip()
                               for parameter in parameter_str[0].split(','))
    return MSCLCommand(command_word, *command_parameter_tuple)
