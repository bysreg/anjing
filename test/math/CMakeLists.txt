include_directories(
	${ANJING_INCLUDE_DIR}
	${GTEST_INCLUDE_DIR}
)

add_executable(tvec3_test tvec3_test.cpp)
set_target_properties(tvec3_test PROPERTIES COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} ")
target_link_libraries(tvec3_test amath gtest gtest_main)

add_test(tVec3Test tvec3_test)