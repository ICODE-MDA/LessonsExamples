cmake_minimum_required(VERSION 2.8)
project( fusionApp )
FILE(GLOB SOURCE_FILES *.cpp)

if(NOT DEFINED BOOST_INCLUDE_DIR)
	set(BOOST_INCLUDE_DIR "" CACHE PATH "BOOST Include Directory")
endif()

if(IS_DIRECTORY ${BOOST_INCLUDE_DIR})
	message(STATUS "BOOST Include Directory: ${BOOST_INCLUDE_DIR}")
else()	
	message(SEND_ERROR "BOOST_INCLUDE_DIR must be set to a directory!")
endif()

if(NOT DEFINED BOOST_LIBRARY_PATH)
	set(BOOST_LIBRARY_PATH "" CACHE PATH "BOOST library Directory")
endif()

if(IS_DIRECTORY ${BOOST_LIBRARY_PATH})
	message(STATUS "BOOST library Directory: ${BOOST_LIBRARY_PATH}")
else()	
	message(SEND_ERROR "BOOST_LIBRARY_PATH must be set to a directory!")
endif()

FILE(GLOB BOOST_LIBRARIES ${BOOST_LIBRARY_PATH}/*.lib)
if(NOT BOOST_LIBRARIES)
	message(FATAL_ERROR "Boost library path is incorrect, it must point to the directory where the .lib files are in your Boost installation")
endif()

set(LIBRARIES ${BOOST_LIBRARIES} )
set(INCLUDES ${BOOST_INCLUDE_DIR})
add_executable( fusionApp ${SOURCE_FILES} )
include_directories( fusionApp ${INCLUDES})
target_link_libraries( fusionApp ${LIBRARIES} )

message(STATUS "====Project: fusionApp ====")
message(STATUS "====USING THE FOLLOWING LOCATIONS====") 
message(STATUS "SOURCE FILES:			${SOURCE_FILES}")
message(STATUS "BOOST_INCLUDE_DIR:		${BOOST_INCLUDE_DIR}")
message(STATUS "BOOST_LIBRARIES:		${BOOST_LIBRARIES}")
