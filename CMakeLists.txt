cmake_minimum_required(VERSION 2.8)
project(anjing)

if(WIN32)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/windows)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

option(build_test "build_test" OFF)

if(build_test)
	message("tests will be build")
	enable_testing()
	find_package(GTest REQUIRED)
	add_subdirectory(test)
endif()

add_subdirectory(src)
