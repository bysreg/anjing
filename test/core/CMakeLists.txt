include_directories(
	${ANJING_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR}
	${GTEST_INCLUDE_DIR}
)

add_executable(test_core core_test.cpp game_object_test.cpp transform_test.cpp)
target_link_libraries(test_core core app gfx ${GLEW_LIBRARY} gtest gtest_main ${SDL2_LIBRARY})
set_target_properties(test_core PROPERTIES COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} ")

add_executable(test_memory_operator memory_operator_test.cpp)
target_link_libraries(test_memory_operator core app ${GLEW_LIBRARY} gtest gtest_main ${SDL2_LIBRARY} )
set_target_properties(test_memory_operator PROPERTIES COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} ")
# we need to define these because the test relies on these defines
target_compile_definitions(test_memory_operator PRIVATE ANJING_REPLACE_GLOBAL_NEW_DELETE_FILE_LINE)

add_test(NAME TestCore COMMAND test_core)
add_test(NAME TestMemoryOperator COMMAND test_memory_operator)