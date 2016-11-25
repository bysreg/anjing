cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(anjing)

set(CMAKE_CXX_STANDARD 11) # use c++11

########## PLATFORM CONFIGURATION #######
if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DANJING_WINDOWS -D_CRT_SECURE_NO_DEPRECATE")
endif()
#========================================

########## DEBUG CONFIGURATION ########
## This will add some debugging macro if debug configuration is on
## To switch on debug configuration in linux, supply cmake with
##  -DCMAKE_BUILD_TYPE=Debug
## For Windows, change to Debug mode in Visual Studio

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DANJING_DEBUG")

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

######## WARNING CONFIGURATION ########
## turn on warning flags
if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX ")

	# suppress some harmless warning on clang-cl on windows
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Qunused-arguments -Wno-unknown-pragmas -Wno-macro-redefined -Wno-deprecated-declarations")
	endif()

else()
	# for linux/osx OS using gcc/clang
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wold-style-cast -Werror")
endif()
#=====================================

######## PROJECT DEPENDENCIES #########
if(WIN32)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/windows)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

if(WIN32)
	macro(USE_WIN_DEBUG_LIB DEBUG_VAR)
		foreach(LIBRARY_PATH ${ARGN})
			get_filename_component(LIBRARY_NAME ${LIBRARY_PATH} NAME_WE) 
			get_filename_component(LIBRARY_DIR ${LIBRARY_PATH} DIRECTORY)
			# message("iter test library path " ${LIBRARY_PATH})
			set(${DEBUG_VAR} ${${DEBUG_VAR}} optimized ${LIBRARY_PATH} debug ${LIBRARY_DIR}/${LIBRARY_NAME}_d.lib)
		endforeach()
	endmacro()

	USE_WIN_DEBUG_LIB(SDL2_WIN_LINK_LIBRARY ${SDL2_LIBRARY})
	USE_WIN_DEBUG_LIB(SDL2_WIN_LINK_LIBRARY ${GLEW_LIBRARY})

	set(SDL2_LIBRARY ${SDL2_WIN_LINK_LIBRARY})
	set(GLEW_LIBRARY ${GLEW_WIN_LINK_LIBRARY})
	
	message("SDL2_LIBRARY var is replaced with : " ${SDL2_LIBRARY})
	message("GLEW_LIBRARY var is replaced with : " ${GLEW_LIBRARY})

endif()

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
	
	# Disable warning for gtest
	set_property(TARGET gtest APPEND_STRING PROPERTY COMPILE_FLAGS " -w")
	add_subdirectory(test)
endif()
######################################
