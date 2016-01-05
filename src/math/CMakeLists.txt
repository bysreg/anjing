include_directories(
	${ANJING_INCLUDE_DIR}	
)

# add target amath (math is reserved word in cmake)
add_library(amath tvec3.hpp tvec3.cpp)

set_target_properties(amath PROPERTIES COMPILE_FLAGS "${PROGRAM_COMPILE_FLAGS} ")