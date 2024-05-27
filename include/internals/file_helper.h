#ifndef MUZZLE_INTERNALS_FILE_HELPER_H
#define MUZZLE_INTERNALS_FILE_HELPER_H

#include "backend.h"
#include <stdio.h>

// returned buffer needs to be freed by caller
MZ_API char* internals_read_file(FILE** file, const char* filepath, const char* msg_on_file_error, const char* msg_on_malloc_error);

#endif // MUZZLE_INTERNALS_FILE_HELPER_H
