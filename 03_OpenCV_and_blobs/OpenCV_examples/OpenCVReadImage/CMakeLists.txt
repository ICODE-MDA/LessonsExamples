cmake_minimum_required(VERSION 2.8)
project( openCvReadImage )
#find_package( OpenCV REQUIRED )
add_executable( openCvReadImage openCvReadImage )
include_directories( openCvReadImage ${OPENCV_INCLUDE_DIR})
target_link_libraries( openCvReadImage ${OPENCV_LIBRARIES} )
