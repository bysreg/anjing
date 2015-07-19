cmake_minimum_required(VERSION 2.8)
project(anjing)

if(WIN32)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/../windows)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)

# list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
# find_package(GLEW)
# if (NOT GLEW_FOUND)
# 	add_subdirectory(glew)
# endif()

add_subdirectory(app)
add_subdirectory(myapp)
