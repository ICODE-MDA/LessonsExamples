@echo off

set OLDPATH=%PATH%

call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat"

set PATH="C:\Program Files (x86)\CMake 2.8\bin";%PATH%

call cmake_arguments.bat

set PATH=%OLDPATH%
set OLDPATH=

pause
