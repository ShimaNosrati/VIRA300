# Initial Setup

## Before you start

* For the following instructions to work, you need to make sure that you have access to https://pypi.org on your machine
  as the libraries will be installed from there.
* The exact version an checksum of the files that will be downloaded are listed in the Pipfile.lock file.
* You won't need access to pypi after installing the libraries unless you want to install new ones or update those that
  are already installed.

## Configuring your environment

1. Download and install the latest *Python 3.8 for Windows* from https://www.python.org/downloads/windows/
2. Run PythonCommandVenv.bat

## Running the sample
1. To launch the application, use:
      ````
      .venv\Scripts\python.exe PythonCommand.py
      ````

## Command line application 

* tasks.py contain some functionalities that can be called in command line
1. Open a command prompt in the project's root directory
2. To get available tasks:
     ````
     .venv\Scripts\invoke.exe --list
     ````
3. example: to run a command on an inspect module
     ````
     .venv\Scripts\invoke.exe iminspect.execute "MY MSCL COMMAND(\"str\", 1)"
     ````
