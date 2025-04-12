from commandcenter import CommandCenterWrapper
from invoke import task, Collection
import pwktypelib
import util
import workspacemanager

"""
Contains callable task in a command line with invoke library
"""

ns = Collection()


def format_unsupported_module_name(name):
    """
    Get string for unsupporte module name
    :param name: name
    """
    return f"{name} module is not supported"


@task
def launch(c, name):
    """
    Launch a module
    :param c: context
    :param name: name of module
    """
    try:
        name = util.format_module_name(name)
    except NotImplementedError:
        print(format_unsupported_module_name(name))
        return
    info = pwktypelib.get_info_from_reg(util.format_prog_id(name))
    if not util.program_running(info.path):
        wm = workspacemanager.WorkspaceManagerWrapper.from_module(name)
        if name == util.EModuleNames.WORKSPACE_MANAGER:
            print(f'Launch {name}... {util.program_running(info.path)}')
            return
        res = wm.start_module() is not None
        print(f'Launch {name}... {res}')


@task
def projects(c, name):
    """
    Enumerate running project of a module type
    :param c: context
    :param name: name of module
    """
    try:
        name = util.format_module_name(name)
    except NotImplementedError:
        print(format_unsupported_module_name(name))
        return
    print(f'Listing all project in module {name}')
    wm = workspacemanager.WorkspaceManagerWrapper.from_module(name)
    if wm is not None:
        for path, project in wm.get_all_projects_of_running_module():
            print(f"{project}")
            return
    print("Failed to query IIMWorkspaceManager")


@task(iterable=["name"])
def setup(c, name):
    """
    Load typelib for a module
    :param c: context
    :param name: modules
    """
    #(generate code in comtpyes.gen)
    for module_name in name:
        print(f'Loading typelib for {module_name}')
        try:
            pwktypelib.get_type_lib(module_name)
        except NotImplementedError:
            continue
            raise RuntimeError(f"Typelib for {module_name} was not found")


"""
task relevant to the shared variable collection
"""


@task(optional=['project'])
def set_shared_variable_iminspect(c, value, var="", project=None):
    """
    Set a shared variable
    :param c: context
    :param value: value of shared variable
    :param var: name of shared variable
    :param project: name of project running module
    """
    res = CommandCenterWrapper.from_module(util.EModuleNames.IMINSPECT, project).set_shared_variable_value(var, value)
    print(f"Setting {var} value to {value} ... {res}")


@task(optional=['project'])
def get_shared_variable_iminspect(c, var="", project=None):
    """
    Get a shared variable
    :param c: context
    :param var: name of shared variable
    :param project: name of project running module
    """
    value = CommandCenterWrapper.from_module(util.EModuleNames.IMINSPECT, project).get_shared_variable_value(var)
    print(f"Getting value of {var} ... {value}")


@task(optional=['project'])
def set_shared_variable_imedit(c, value, var="", project=None):
    """
    Set a shared variable
    :param c: context
    :param value: value of shared variable
    :param var: name of shared variable
    :param project: name of project running module
    """
    res = CommandCenterWrapper.from_module(util.EModuleNames.IMEDIT, project).set_shared_variable_value(var, value)
    print(f"Setting {var} value to {value} ... {res}")


@task(optional=['project'])
def get_shared_variable_imedit(c, var="", project=None):
    """
    Get a shared variable
    :param c: context
    :param var: name of shared variable
    :param project: name of project running module
    """
    value = CommandCenterWrapper.from_module(util.EModuleNames.IMEDIT, project).get_shared_variable_value(var)
    print(f"Getting value of {var} ... {value}")


"""
task relevant to the iminspect collection
"""


@task(optional=['project'])
def execute_iminspect(c, cmd="", project=None):
    """
    Execute an MSCL command
    :param c: context
    :param cmd: MSCL command
    :param project: name of project running module
    """
    res = CommandCenterWrapper.from_module(util.EModuleNames.IMINSPECT, project).execute_command(cmd)
    print(f"Executing {cmd} ... {res}")


@task(optional=['project'])
def execute_get_iminspect(c, cmd="", project=None):
    """
    Execute an MSCL command and print output
    :param c: context
    :param cmd: MSCL command
    :param project: name of project running module
    """
    print(f"Executing {cmd} ...")
    print(CommandCenterWrapper.from_module(util.EModuleNames.IMINSPECT, project).execute_get_command(cmd))


"""
task relevant to the iminspect collection
"""


@task(optional=['project'])
def execute_imedit(c, cmd="", project=None):
    """
    Execute an MSCL command
    :param c: context
    :param cmd: MSCL command
    :param project: name of project running module
    """
    res = CommandCenterWrapper.from_module(util.EModuleNames.IMEDIT, project).execute_command(cmd)
    print(f"Executing {cmd} ... {res}")


@task(optional=['project'])
def execute_get_imedit(c, cmd="", project=None):
    """
    Execute an MSCL command and print output
    :param c: context
    :param cmd: MSCL command
    :param project: name of project running module
    """
    print(f"Executing {cmd} ...")
    print(CommandCenterWrapper.from_module(util.EModuleNames.IMEDIT, project).execute_get_command(cmd))


# add to available task list
ns.add_task(launch)
ns.add_task(projects)
ns.add_task(setup)

# add to iminspect collection
shared_variable_iminspect = Collection('shared_variable')
shared_variable_iminspect.add_task(set_shared_variable_iminspect, "set")
shared_variable_iminspect.add_task(get_shared_variable_iminspect, "get")
iminspect = Collection('iminspect')
iminspect.add_task(execute_iminspect, "execute")
iminspect.add_task(execute_get_iminspect, "execute-print")
iminspect.add_collection(shared_variable_iminspect, "shared_variable")
ns.add_collection(iminspect, "iminspect")

# add to imedit collection
shared_variable_imedit = Collection('shared_variable')
shared_variable_imedit.add_task(set_shared_variable_imedit, "set")
shared_variable_imedit.add_task(get_shared_variable_imedit, "get")
imedit = Collection('imedit')
imedit.add_task(execute_imedit, "execute")
imedit.add_task(execute_get_imedit, "execute-print")
imedit.add_collection(shared_variable_imedit, "shared_variable")
ns.add_collection(imedit, "imedit")
