include_directories(
	${ANJING_INCLUDE_DIR}
	${GTEST_INCLUDE_DIR}
)

add_executable(core_test core_test.cpp)
target_link_libraries(core_test core app ${GLEW_LIBRARY} gtest gtest_main ${SDL2_LIBRARY})

add_executable(memory_operator_test memory_operator_test.cpp)
target_link_libraries(memory_operator_test core app ${GLEW_LIBRARY} gtest gtest_main ${SDL2_LIBRARY} )
target_compile_definitions(core PRIVATE ANJING_REPLACE_GLOBAL_NEW_DELETE_FILE_LINE)

add_test(coreTest core_test)
add_test(memoryOperatorTest memory_operator_test)
