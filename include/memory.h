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
    #define MZ_REALLOC(ptr, size)   realloc(ptr, size)
#endif

#ifdef __MEMORY_CREATE_RLGL_MIRRORS__
    #define RLGL_MALLOC                 MZ_MALLOC
    #define RLGL_CALLOC                 MZ_CALLOC
    #define RLGL_FREE                   MZ_FREE
    #define RLGL_REALLOC                MZ_REALLOC
#endif