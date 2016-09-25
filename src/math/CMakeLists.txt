include_directories(
	${ANJING_INCLUDE_DIR}	
)

# add target math
# this traget won't actually produce any binary (because it is, currently, exists as header-only files)
# we need dummy.cpp to fool cmake, because cmake assume library always has at least one "source" file
add_library("math" dummy.cpp tvec2.hpp tvec3.hpp tvec4.hpp tmat4.hpp vecops.hpp matops.hpp tquat)

# this line is needed because without it, cmake will complain that it cannot infer the target language from .hpp file only
set_target_properties("math" PROPERTIES COMPILE_FLAGS "${PROGRAM_COMPILE_FLAGS} " LINKER_LANGUAGE CXX)