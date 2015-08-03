include_directories(
	${ANJING_INCLUDE_DIR}
	${GTEST_INCLUDE_DIRS}
)

add_executable(appTestExecutable app_test.cpp)

target_link_libraries(appTestExecutable app ${SDL2_LIBRARY} ${GLEW_LIBRARY} ${GTEST_MAIN_LIBRARIES})

add_test(appTest appTestExecutable)