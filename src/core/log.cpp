#include "core/log.hpp"
#include "core/util.hpp"
#include <cstdarg>
#include <string>

#define ANJING_LOG_BUFFER_SIZE 2048

void anjing::core::LogFormat(FILE* stream, const char* filename, int line, const char* format, ...)
{
	ANJING_UNUSED(filename);
	ANJING_UNUSED(line);

	va_list params;
	char buf[ANJING_LOG_BUFFER_SIZE];

	if (stream == stdout)
	{
		fprintf(stream, "stdout > ");
	}
	else if (stream == stderr)
	{
		fprintf(stream, "stderr > ");
	}

	va_start(params, format);
	vsnprintf(buf, ANJING_LOG_BUFFER_SIZE, format, params);
	fprintf(stream, "%s", buf);
	va_end(params);
}
