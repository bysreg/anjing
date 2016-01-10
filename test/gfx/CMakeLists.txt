include_directories(
	${ANJING_INCLUDE_DIR}
	${GTEST_INCLUDE_DIR}
)

add_executable(test_gfx mesh_renderer_test.cpp mesh_test.cpp)
set_target_properties(test_gfx PROPERTIES COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} ")
target_link_libraries(test_gfx app core gfx ${GLEW_LIBRARY} gtest gtest_main ${SDL2_LIBRARY} )

add_test(TestGfx test_gfx)