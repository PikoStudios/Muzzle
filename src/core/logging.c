#include "core/logging.h"
#include "backend.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void mz_log_status(mz_log_status_type type, const char* status)
{
	switch (type)
	{
	case LOG_STATUS_WARNING:
		printf("\e[0;33m\e[4;33m[WARNING] :: %s\e[0m\n", status);
		break;

	case LOG_STATUS_ERROR:
		printf("\e[0;31m\e[4;31m[ERROR] :: %s\e[0m\n", status);
		break;

	case LOG_STATUS_FATAL_ERROR:
		printf("\e[0;31m\e[4;31m[FATAL] :: %s\e[0m\n", status);
		glfwTerminate();
		exit(-1);
		break;

	case LOG_STATUS_SUCCESS:
		printf("\e[0;32m\e[4;32m[SUCCESS] :: %s\e[0m\n", status);
		break;

	case LOG_STATUS_INFO:
		printf("\e[0;34m\e[4;34m[INFO] :: %s\n\e[0m", status);
		break;

	default:
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Unknown status type '%d'", type);
		break;
	}
}

void mz_log_status_formatted(mz_log_status_type type, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

#if defined(_MSC_VER) && _MSC_VER < 1900
	#define VA_SNPRINTF(buffer, length, format, argptr) _vsnprintf(buffer, length, format, argptr)
#else
	#define VA_SNPRINTF(buffer, length, format, argptr) vsnprintf(buffer, length, format, argptr)
#endif

	const int fmt_len = VA_SNPRINTF(NULL, 0, fmt, args);
	MZ_ASSERT_DETAILED(fmt_len > -1, "vsnprintf failed for some reason");

	char buf[fmt_len + 1];

	VA_SNPRINTF(buf, sizeof(buf), fmt, args);
	MZ_ASSERT_DETAILED(buf[fmt_len] == '\0', "vsnprintf failed to null terminate string");

	mz_log_status(type, buf);
	va_end(args);
}
