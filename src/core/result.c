#include "core/result.h"
#include "core/logging.h"

MZ_API noreturn void* __mz_unwrap_error(const char* func, const char* file, int line)
{
// holy ugly :(
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-noreturn"
	mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Unwrapped error result in %s (%s:%d)", func, file, line);
}

#pragma GCC diagnostic pop
