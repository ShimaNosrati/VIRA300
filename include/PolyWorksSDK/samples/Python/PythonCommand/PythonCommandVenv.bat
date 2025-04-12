py -3 -m venv %CD%\.venv
.venv\Scripts\python -m pip install -r %CD%\requirements.txt
.venv\Scripts\invoke setup --name IMInspect --name WorkspaceManager
