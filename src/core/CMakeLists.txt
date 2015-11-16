include_directories(
	${ANJING_INCLUDE_DIR}	
)

# add target core
add_library(core memory_manager.cpp log.cpp)

set_target_properties(core PROPERTIES COMPILE_FLAGS "${ANJING_COMPILE_FLAGS} ")