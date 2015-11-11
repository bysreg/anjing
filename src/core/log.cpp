#include "core/log.hpp"
#include <cstdarg>

void anjing::Log(const char* filename, int line, const char* format, ...) {
	va_list params;
	char buf[2048];

	va_start(params, format);
	vsprintf(buf, format, params);
	printf("%s", buf);
	va_end(params);
}