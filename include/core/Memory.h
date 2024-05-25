#ifndef MUZZLE_CORE_MEMORY_H
#define MUZZLE_CORE_MEMORY_H

#include <stdlib.h>

#ifndef MZ_MALLOC
	#define MZ_MALLOC(size) malloc(size)
#endif

#ifndef MZ_CALLOC
	#define MZ_CALLOC(num, size) calloc(num, size)
#endif

#ifndef MZ_FREE
	#define MZ_FREE(ptr) free(ptr)
#endif

#ifndef MZ_REALLOC
	#define MZ_REALLOC(ptr, size) __mz_memory_reallocate(ptr, size)
#endif

void* __mz_memory_reallocate(void* ptr, size_t size);

#endif // MUZZLE_CORE_MEMORY_H
