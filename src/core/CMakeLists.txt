include_directories(
	${ANJING_INCLUDE_DIR}
)

# add target core
add_library(core memory_manager.cpp memory_manager.hpp log.cpp log.hpp util.cpp util.hpp component.hpp forced_include.hpp game_object.cpp game_object.hpp)

set_target_properties(core PROPERTIES COMPILE_FLAGS "${PROGRAM_COMPILE_FLAGS} ")