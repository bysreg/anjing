include_directories(
	${ANJING_INCLUDE_DIR}
)

# add target core
add_library(core memory_manager.cpp memory_manager.hpp log.cpp log.hpp util.cpp util.hpp component.hpp forced_include.hpp game_object.cpp game_object.hpp types.hpp scene.cpp scene.hpp singleton.hpp transform.hpp transform.cpp noncopyable.hpp assert.hpp)

target_link_libraries(core gfx ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

set_target_properties(core PROPERTIES COMPILE_FLAGS "${PROGRAM_COMPILE_FLAGS} ")