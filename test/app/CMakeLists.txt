include_directories(
	${ANJING_INCLUDE_DIR}
	${GTEST_INCLUDE_DIR}
)

add_executable(app_test app_test.cpp)
target_link_libraries(app_test app ${GLEW_LIBRARY} gtest gtest_main ${SDL2_LIBRARY} )

add_test(appTest app_test)