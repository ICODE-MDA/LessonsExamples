@echo off
set OLDPATH=%PATH%
set THIRD_PARTY=C:\libraries\ossim-3rd-party-vs2010\bin\win32
set OSSIM_INSTALL=C:\libraries\ossim_install\bin
set PATH=%THIRD_PARTY%;%OSSIM_INSTALL%

ossimTileToIplFilterApp.exe %1

set PATH=%OLDPATH%
set OLDPATH=
