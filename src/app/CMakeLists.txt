include_directories(
	${ANJING_INCLUDE_DIR}
	${SDL2_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR}
)

add_library(app app.cpp)
