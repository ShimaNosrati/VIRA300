py -3 -m venv %CD%\.venv
.venv\Scripts\python -m pip install -r %CD%\requirements.txt
.venv\Scripts\python SharedVariableParser.py --l DEBUG --m WorkspaceManager IMInspect