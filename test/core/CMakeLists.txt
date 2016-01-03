include_directories(
	${ANJING_INCLUDE_DIR}
	${GTEST_INCLUDE_DIR}
)

add_executable(core_test core_test.cpp)
target_link_libraries(core_test core app ${GLEW_LIBRARY} gtest gtest_main ${SDL2_LIBRARY})
set_target_properties(core_test PROPERTIES COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} ")


add_executable(memory_operator_test memory_operator_test.cpp)
target_link_libraries(memory_operator_test core app ${GLEW_LIBRARY} gtest gtest_main ${SDL2_LIBRARY} )
set_target_properties(memory_operator_test PROPERTIES COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} ")
# we need to define these because the test relies on these defines
target_compile_definitions(memory_operator_test PRIVATE ANJING_REPLACE_GLOBAL_NEW_DELETE_FILE_LINE)

add_executable(game_object_test game_object_test.cpp)
target_link_libraries(game_object_test core app ${GLEW_LIBRARY} gtest gtest_main ${SDL2_LIBRARY} )
set_target_properties(game_object_test PROPERTIES COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} ")

add_test(coreTest core_test)
add_test(memoryOperatorTest memory_operator_test)
add_test(gameObjectTest game_object_test)