include_directories(
	${ANJING_INCLUDE_DIR}
	${GTEST_INCLUDE_DIRS}
)

add_executable(appTestExecutable app_test.cpp)

target_link_libraries(appTestExecutable app ${GLEW_LIBRARY} ${GTEST_MAIN_LIBRARIES} ${GTEST_LIBRARIES} ${SDL2_LIBRARY} )

add_test(appTest appTestExecutable)