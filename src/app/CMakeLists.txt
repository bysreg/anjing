include_directories(
	${ANJING_INCLUDE_DIR}
	${SDL2_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR}
)

# add target app
add_library(app app.cpp app.hpp)

set_target_properties(app PROPERTIES COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} ")