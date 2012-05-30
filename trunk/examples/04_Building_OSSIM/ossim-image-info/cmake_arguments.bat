set common_dir="C:\development\3rd-party-vs10-2010-express\vs2010"
set common_lib=%common_dir%/lib/win32
set ossim_trunk_dir="C:\development\ossim_trunk_latest"
set ossim_install_dir="C:\development\ossim_build\Release"

cmake -G "Visual Studio 10"^
 -DCMAKE_BUILD_TYPE=Release^
 -DCMAKE_INCLUDE_PATH=%common_dir%/include^
 -DOPENCV_INCLUDE_DIR=%common_dir%/include^
 -DOPENCV_LIBRARIES=%common_lib%/cv210.lib;%common_lib%/cvaux210.lib;%common_lib%/cxcore210.lib;%common_lib%/cxts210.lib;%common_lib%/ml210.lib;%common_lib%/highgui210.lib^
 -DOSSIM_INCLUDE_DIR=%ossim_trunk_dir%/ossim/include^
 -DOSSIM_LIBRARIES=%ossim_install_dir%/ossim.lib^
 .
