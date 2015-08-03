include_directories(
	${PROJECT_SOURCE_DIR}
	${GTEST_INCLUDE_DIRS}
)

add_executable(appTestExecutable app_test.cpp)

target_link_libraries(appTestExecutable app ${SDL2_LIBRARY} ${GLEW_LIBRARY})

add_test(appTest appTestExecutable)