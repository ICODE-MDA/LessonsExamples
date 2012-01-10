set common_dir="C:/libraries/ossim-3rd-party-vs2010"
set common_lib=%common_dir%/lib/win32

cmake -G "Visual Studio 10"^
 -DCMAKE_BUILD_TYPE=Release^
 -DCMAKE_INCLUDE_PATH=%common_dir%/include^
 -DOPENCV_INCLUDE_DIR=%common_dir%/include^
 -DOPENCV_LIBRARIES=%common_lib%/cv210.lib;%common_lib%/cvaux210.lib;%common_lib%/cxcore210.lib;%common_lib%/cxts210.lib;%common_lib%/ml210.lib;%common_lib%/highgui210.lib^
 .
