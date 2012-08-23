@echo off

set OLDPATH=%PATH%

call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat"

set PATH="C:\Program Files (x86)\Cmake 2.8\bin";%PATH%
set ossim_src_dir="C:/ossim/trunk"
set ossim_install_dir="C:/ossim/trunk/build"
set ossim_lib=%ossim_install_dir%/Release

cmake -G "Visual Studio 10"^
 -DCMAKE_BUILD_TYPE=Release^
 -DCMAKE_INCLUDE_PATH=%common_dir%/include^
 -DOSSIM_INCLUDE_DIR=%ossim_src_dir%/ossim/include^
 -DOSSIM_LIBRARIES=%ossim_lib%/ossim.lib^
 .


set PATH=%OLDPATH%
set OLDPATH=
