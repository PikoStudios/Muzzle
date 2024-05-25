#ifndef MUZZLE_CORE_LOGGING_H
#define MUZZLE_CORE_LOGGING_H

#include "../backend.h"

typedef enum mz_log_status_type
{
	// Yellow text
	LOG_STATUS_WARNING,

	// Red text
	LOG_STATUS_ERROR,

	// Red text and exit to desktop
	LOG_STATUS_FATAL_ERROR,

	// Green text
	LOG_STATUS_SUCCESS,

	// Blue text
	LOG_STATUS_INFO
} mz_log_status_type;

MZ_API void mz_log_status(mz_log_status_type type, const char* status);
MZ_API void mz_log_status_formatted(mz_log_status_type type, const char* fmt, ...);

#endif // MUZZLE_CORE_LOGGING_H
