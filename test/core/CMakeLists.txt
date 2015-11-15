include_directories(
	${ANJING_INCLUDE_DIR}
	${GTEST_INCLUDE_DIR}
)

add_executable(coreTestExecutable core_test.cpp)
target_link_libraries(coreTestExecutable core app ${GLEW_LIBRARY} gtest gtest_main ${SDL2_LIBRARY} )

add_test(coreTest coreTestExecutable)