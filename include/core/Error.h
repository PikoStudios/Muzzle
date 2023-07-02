#ifndef MUZZLE_CORE_ERROR_H
#define MUZZLE_CORE_ERROR_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "../backend.h"

enum _mz_status_types
{
	// Yellow Text
	STATUS_WARNING,
	// Red Text
	STATUS_ERROR,
	// Red Text, exit, and attempt to clean up resources
	STATUS_FATAL_ERROR,
	// Red Text and exit but do not attempt to clean up resources. (Not recommended)
	STATUS_FATAL_ERROR_DONT_CLEAN_UP,
	// Green text
	STATUS_SUCCESS,
	// Blue text
	STATUS_INFO
};

typedef enum _mz_status_types status_types;

MZ_API void log_status(status_types type, const char* status);
MZ_API void log_status_formatted(status_types type, const char* fmt, ...);

#endif // MUZZLE_CORE_ERROR_H