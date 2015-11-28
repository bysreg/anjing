#include "core/log.hpp"
#include "core/util.hpp"
#include <cstdarg>

#define ANJING_LOG_BUFFER_SIZE 2048

void anjing::Log(const char* filename, int line, const char* format, ...) {
	ANJING_UNUSED(filename);
	ANJING_UNUSED(line);

	va_list params;
	char buf[ANJING_LOG_BUFFER_SIZE];

	va_start(params, format);
	vsnprintf(buf, ANJING_LOG_BUFFER_SIZE, format, params);
	printf("%s", buf);
	va_end(params);
}