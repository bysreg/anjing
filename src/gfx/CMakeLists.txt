include_directories(
	${ANJING_INCLUDE_DIR}
	${SDL2_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR}
)

# add target gfx
add_library(gfx mesh_renderer.cpp mesh_renderer.hpp mesh.cpp mesh.hpp vertex.hpp shader.cpp shader.hpp material.hpp material.cpp renderer.cpp renderer.hpp camera.hpp camera.cpp)

target_link_libraries(gfx core ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

set_target_properties(gfx PROPERTIES COMPILE_FLAGS "${PROGRAM_COMPILE_FLAGS} ")