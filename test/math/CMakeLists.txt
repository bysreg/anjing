include_directories(
	${ANJING_INCLUDE_DIR}
	${GTEST_INCLUDE_DIR}
)

add_executable(test_math tvec2_test.cpp tvec3_test.cpp tvec4_test.cpp tmat4_test.cpp tquat_test)
set_target_properties(test_math PROPERTIES COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} ")
target_link_libraries(test_math gtest gtest_main)

add_test(NAME TestMath COMMAND test_math)