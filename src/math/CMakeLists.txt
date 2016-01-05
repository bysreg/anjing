include_directories(
	${ANJING_INCLUDE_DIR}	
)

# add target math
# this traget won't actually produce any binary (because it is, currently, exists as header-only files)
##add_library("math" tvec3.hpp)

# this line is needed because without it, cmake will complain that it cannot infer the target language from .hpp file only
##set_target_properties("math" PROPERTIES COMPILE_FLAGS "${PROGRAM_COMPILE_FLAGS} " LINKER_LANGUAGE CXX)