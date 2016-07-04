include_directories(
	${ANJING_INCLUDE_DIR}
	${GTEST_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR}
	${SDL2_INCLUDE_DIR}
)

add_executable(test_gfx vertex_test.cpp mesh_renderer_test.cpp mesh_test.cpp shader_test.cpp material_test.cpp)
set_target_properties(test_gfx PROPERTIES COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} ")
target_link_libraries(test_gfx app core gfx ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} gtest gtest_main ${SDL2_LIBRARY} )

add_test(NAME TestGfx COMMAND test_gfx)