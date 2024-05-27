#ifndef MUZZLE_INTERNALS_TODO_H
#define MUZZLE_INTERNALS_TODO_H

#include "core/logging.h"

#define TODO() mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "%s has not yet been implemented", __func__);

#endif // MUZZLE_INTERNALS_TODO_H
