cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(anjing)

set(CMAKE_CXX_STANDARD 11) # use c++11

########## DEBUG CONFIGURATION ########
## This will add some debugging macro if debug configuration is on
## To switch on debug configuration in linux, supply cmake with
##  -DCMAKE_BUILD_TYPE=Debug
## For Windows, change to Debug mode in Visual Studio

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DANJING_DEBUG")

## turn on warning flags
if(WIN32)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4")
else()
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
endif()

######################################

if(WIN32)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/windows)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(ANJING_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src")

##### project-wide compile flags #####
set(ANJING_COMPILE_FLAGS "")

## custom compile flags : 
# force include defines.hpp
set(MYAPP_FORCED_INCLUDE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/myapp/defines.hpp")
if(WIN32)
	set(ANJING_COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} /FI\"${MYAPP_FORCED_INCLUDE_FILE}\" ")
else()
	set(ANJING_COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} -include\"${MYAPP_FORCED_INCLUDE_FILE}\" ")
endif()

######################################

add_subdirectory(src)

############## TESTS #################
option(build_test "build_test" OFF)
if(build_test)
	
	if(WIN32)
		#this will override gtest_force_shared_crt that is set by googletest's CMakeLists
		#we do this because googletest' cmake is build as static lib, but other projects in windows is built with runtime library set to dynamic
		option(gtest_force_shared_crt ON)
		set(gtest_force_shared_crt ON)	
	endif()
	
	add_subdirectory(src/third_party/googletest)	
	
	message("tests will be build")
	enable_testing()
	
	# Include the gtest library. gtest_SOURCE_DIR is available due to googletest's CMakeLists	
	set(GTEST_INCLUDE_DIR ${gtest_SOURCE_DIR}/include)
	
	#find_package(GTest REQUIRED)
	add_subdirectory(test)
endif()
######################################