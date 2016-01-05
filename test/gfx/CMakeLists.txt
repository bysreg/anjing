include_directories(
	${ANJING_INCLUDE_DIR}
	${GTEST_INCLUDE_DIR}
)

add_executable(mesh_renderer_test mesh_renderer_test.cpp)
set_target_properties(mesh_renderer_test PROPERTIES COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} ")
target_link_libraries(mesh_renderer_test app core gfx ${GLEW_LIBRARY} gtest gtest_main ${SDL2_LIBRARY} )

add_test(meshRendererTest mesh_renderer_test)