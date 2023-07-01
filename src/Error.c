#include "core/Error.h"

MZ_API void log_status(status_types type, const char* status)
{
	switch (type)
	{
	case STATUS_FATAL_ERROR:
		fprintf(stderr, "\e[0;31m\e[4;31m[FATAL] :: %s\n\e[0m", status);
		exit(-1);
		break;
	case STATUS_WARNING:
		printf("\e[0;33m\e[4;33m[WARNINGS] :: %s\n\e[0m", status);
		break;
	case STATUS_ERROR:
		fprintf(stderr, "\e[0;31m\e[4;31m[ERROR] :; %s\n\e[0m", status);
		break;
	case STATUS_SUCCESS:
		printf("\e[0;32m\e[4;32m[SUCCESS] :: %s\n\e[0m", status);
		break;
	
	case STATUS_INFO:
		printf("\e[0;34m\e[4;34m[INFO] :: %s\n\e[0m", status);
		break;
	
	default:
		fprintf(stderr, "\e[0;31m\e[4;31m[FATAL] :: Unknown status type '%d'\n\e[0m", type);
		exit(-1);
		break;
	}
}

MZ_API void log_status_formatted(status_types type, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	char buffer[(MUZZLE_STRING_FMT_BUFFER_SIZE + strlen(fmt))];
#if defined(_MSC_VER) && _MSC_VER < 1900
	memset(buffer, 0, sizeof(buffer));
	_vsnprintf(buffer, sizeof(buffer), fmt, args);
#else
	vsnprintf(buffer, sizeof(buffer), fmt, args);
#endif
	log_status(type, buffer);
	
	va_end(args);
}