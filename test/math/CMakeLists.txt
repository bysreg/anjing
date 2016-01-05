include_directories(
	${ANJING_INCLUDE_DIR}
	${GTEST_INCLUDE_DIR}
)

add_executable(tvec2_test tvec2_test.cpp)
set_target_properties(tvec2_test PROPERTIES COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} ")
target_link_libraries(tvec2_test gtest gtest_main)

add_executable(tvec3_test tvec3_test.cpp)
set_target_properties(tvec3_test PROPERTIES COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} ")
target_link_libraries(tvec3_test gtest gtest_main)

add_executable(tvec4_test tvec4_test.cpp)
set_target_properties(tvec4_test PROPERTIES COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} ")
target_link_libraries(tvec4_test gtest gtest_main)

add_test(tVec2Test tvec2_test)
add_test(tVec3Test tvec3_test)
add_test(tVec4Test tvec4_test)