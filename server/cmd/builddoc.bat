@echo off

set DOC_DIR=%~dp0..\doc\api

del /f /s /q %DOC_DIR% > nul

pushd %~dp0..\tools\jsdoc_toolkit
@echo on
call ant
@echo off
popd

start %DOC_DIR%\index.html