@echo off

set PROJECT_NAME=Porca
set PROJECT_NAME_SAFE=Porca

set ORCA_DIR=..\..\..\lib\Orca
set STDLIB_DIR=%ORCA_DIR%\src\libc-shim
set SOURCE_DIR=..\code
set DATA_DIR=..\data
set LIB_DIR=..\lib

:: compile wasm module
set wasmFlags=--target=wasm32 --no-standard-libraries -mbulk-memory
set wasmFlags=%wasmFlags% -g -O2
set wasmFlags=%wasmFlags% -D__ORCA__ -DORCA_COMPILATION -DPROJECT_NAME=\"%PROJECT_NAME%\" -DPROJECT_NAME_SAFE=\"%PROJECT_NAME_SAFE%\"
set wasmFlags=%wasmFlags% -Wl,--no-entry -Wl,--export-dynamic -Wl,--no-entry -Wl,--export-dynamic
set wasmFlags=%wasmFlags% -isystem %STDLIB_DIR%\include -I%ORCA_DIR%\src -I%ORCA_DIR%\src\ext -I%LIB_DIR%\include
set cppFlag=-std=c++11
set OrcaSourceFiles=%ORCA_DIR%\src\orca.c %STDLIB_DIR%\src\*.c
set OrcaLibName=orca
set OrcaLibFilename=lib%OrcaLibName%.a

if not exist %OrcaLibFilename% (
	echo [Building %OrcaLibFilename%...]
	clang %wasmFlags% -Wl,--relocatable -o .\%OrcaLibFilename% %OrcaSourceFiles%
	IF %ERRORLEVEL% NEQ 0 EXIT /B %ERRORLEVEL%
)

echo [Building...]
clang %wasmFlags% %cppFlag% -o .\%PROJECT_NAME_SAFE%.wasm -L . -l%OrcaLibName% %SOURCE_DIR%\main.cpp
IF %ERRORLEVEL% NEQ 0 EXIT /B %ERRORLEVEL%

echo [Bundling...]
orca bundle --orca-dir %ORCA_DIR% --name %PROJECT_NAME_SAFE% --icon %DATA_DIR%\Resources\icon256.png --resource-dir %DATA_DIR%\Resources %PROJECT_NAME_SAFE%.wasm

echo [Done!]
