cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(anjing)

set(CMAKE_CXX_STANDARD 11) # use c++11

########## PLATFORM CONFIGURATION #######
if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DANJING_WINDOWS")
endif()
#========================================

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
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -Wold-style-cast")
endif()

#=====================================

######### RELEASE CONFIGURATION ######
## To switch on release configuration in linux, supply cmake with
##  -DCMAKE_BUILD_TYPE=Release
## For Windows, change to Release mode in Visual Studio

## turn on optimization flags
if(WIN32)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

#=====================================

######## PROJECT DEPENDECIES #########
if(WIN32)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/windows)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(ANJING_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src")
#=====================================

##### PROJECT-WIDE COMPILE FLAGS #####
set(ANJING_COMPILE_FLAGS "")

set(ANJING_FORCED_INCLUDE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/core/forced_include.hpp")

## custom compile flags : 
set(USER_COMPILE_FLAGS "")

# force include defines.hpp
set(USER_FORCED_INCLUDE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/myapp/defines.hpp")

# include ANJING_FORCE_INCLUDE_FILE always after USER_FORCED_INCLUDE_FILE
if(WIN32)
	set(USER_COMPILE_FLAGS "${USER_COMPILE_FLAGS} /FI\"${USER_FORCED_INCLUDE_FILE}\" ")
	set(ANJING_COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} /FI\"${ANJING_FORCED_INCLUDE_FILE}\" ")
else()
	set(USER_COMPILE_FLAGS "${USER_COMPILE_FLAGS} -include\"${USER_FORCED_INCLUDE_FILE}\" ")
	set(ANJING_COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} -include\"${ANJING_FORCED_INCLUDE_FILE}\" ")
endif()

# PROGRAM_COMPILE_FLAGS is a combination of both USER_COMPILE_FLAGS and ANJING_COMPILE_FLAGS
# ANJING_COMPILE_FLAGS is specified after USER_COMPILE_FLAGS intentionally
set(PROGRAM_COMPILE_FLAGS "${USER_COMPILE_FLAGS}  ${ANJING_COMPILE_FLAGS}")

#=====================================

######## CODE COVERAGE REPORT ########
option(gen_coverage "gen_coverage" OFF)
if(gen_coverage)
	#this will generate code coverage in debug mode
	message("coverage report will be generated")
	if(NOT WIN32)
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} --coverage")
	endif()
endif()
#=====================================

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
