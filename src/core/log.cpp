#include "core/log.hpp"
#include "core/util.hpp"
#include <cstdarg>
#include <string>

#define ANJING_LOG_BUFFER_SIZE 2048

void anjing::core::Log(FILE* stream, const char* filename, int line, std::string message)
{
	anjing::core::Log(stream, filename, line, message.c_str(), "");
}

void anjing::core::Log(FILE* stream, const char* filename, int line, const char* format, ...) 
{
	ANJING_UNUSED(filename);
	ANJING_UNUSED(line);

	va_list params;
	char buf[ANJING_LOG_BUFFER_SIZE];

	if (stream == stdout)
	{
		fprintf(stream, "out > ");
	}
	else if (stream == stderr)
	{
		fprintf(stream, "err > ");
	}

	va_start(params, format);
	vsnprintf(buf, ANJING_LOG_BUFFER_SIZE, format, params);
	fprintf(stream, "%s", buf);
	va_end(params);
}
