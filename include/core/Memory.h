#pragma once

// This includes all memory management functions used by Muzzle
// It has been seperated so RLGL can also take advantage of these functions

#include <stdlib.h>

#ifndef MZ_MALLOC
    #define MZ_MALLOC(size)         malloc(size)
#endif

#ifndef MZ_CALLOC
    #define MZ_CALLOC(num, size)    calloc(num, size)
#endif

#ifndef MZ_FREE
    #define MZ_FREE(ptr)            free(ptr)
#endif

#ifndef MZ_REALLOC
    #define MZ_REALLOC(ptr, size)   mz_safe_realloc(ptr, size)
#endif

// This function will MZ_FREE(ptr) when realloc fails. 
void* mz_safe_realloc(void* ptr, size_t size);