include_directories(
	${ANJING_INCLUDE_DIR}	
)

add_library(core memory_manager.cpp log.cpp)
