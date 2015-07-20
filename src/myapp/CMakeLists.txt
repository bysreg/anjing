include_directories(
	${PROJECT_SOURCE_DIR}
)

add_executable(myapp main.cpp)

target_link_libraries(myapp app ${SDL2_LIBRARY} ${GLEW_LIBRARY})

install(TARGETS myapp DESTINATION ${PROJECT_SOURCE_DIR}/..)
