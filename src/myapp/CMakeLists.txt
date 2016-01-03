include_directories(
	${ANJING_INCLUDE_DIR}
)

# add target myapp
add_executable(myapp main.cpp defines.hpp)
set_target_properties(myapp PROPERTIES COMPILE_FLAGS "${PROGRAM_COMPILE_FLAGS} ")
target_link_libraries(myapp app core ${SDL2_LIBRARY} ${GLEW_LIBRARY})

install(TARGETS myapp DESTINATION ${PROJECT_SOURCE_DIR})
