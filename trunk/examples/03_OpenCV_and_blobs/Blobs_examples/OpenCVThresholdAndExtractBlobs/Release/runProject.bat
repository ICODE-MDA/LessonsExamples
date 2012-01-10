@echo off
set OLDPATH=%PATH%
set PATH=C:\libraries\ossim-3rd-party-vs2010\bin\win32

OpenCVThresholdAndExtractBlobs.exe ..\puzzle.png 

pause

set PATH=%OLDPATH%
set OLDPATH=