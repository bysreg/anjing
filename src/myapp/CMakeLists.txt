include_directories(
	${ANJING_INCLUDE_DIR}
	${SDL2_INCLUDE_DIR}
)

# add target myapp
add_executable(myapp main.cpp defines.hpp)
set_target_properties(myapp PROPERTIES COMPILE_FLAGS "${PROGRAM_COMPILE_FLAGS} ")
target_link_libraries(myapp app core gfx ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

install(TARGETS myapp DESTINATION ${PROJECT_SOURCE_DIR})
