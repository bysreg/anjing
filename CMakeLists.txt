cmake_minimum_required(VERSION 2.8)
project(anjing)

if(WIN32)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/windows)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(ANJING_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src")

add_subdirectory(src)

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
