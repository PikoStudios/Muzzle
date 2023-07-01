#ifndef MUZZLE_CORE_ERROR_H
#define MUZZLE_CORE_ERROR_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "../backend.h"

enum _mz_status_types
{
	STATUS_WARNING,
	STATUS_ERROR,
	STATUS_FATAL_ERROR,
	STATUS_SUCCESS,
	STATUS_INFO
};

typedef enum _mz_status_types status_types;

MZ_API void log_status(status_types type, const char* status);
MZ_API void log_status_formatted(status_types type, const char* fmt, ...);

#endif // MUZZLE_CORE_ERROR_H