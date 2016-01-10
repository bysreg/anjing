include_directories(
	${ANJING_INCLUDE_DIR}
	${GTEST_INCLUDE_DIR}
)

add_executable(test_app app_test.cpp)
set_target_properties(test_app PROPERTIES COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} ")
target_link_libraries(test_app app core ${GLEW_LIBRARY} gtest gtest_main ${SDL2_LIBRARY} )

add_test(NAME TestApp COMMAND test_app)