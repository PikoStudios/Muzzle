#ifndef MUZZLE_CORE_MEMORY_H
#define MUZZLE_CORE_MEMORY_H

#ifndef MUZZLE_EXCLUDE_STDLIB
	#include <stdlib.h>
#endif

#ifndef MZ_MALLOC
	#define MZ_MALLOC(size)			malloc(size)
#endif

#ifndef MZ_CALLOC
	#define MZ_CALLOC(num, size)	calloc(num,size)
#endif

#ifndef MZ_FREE
	#define MZ_FREE(ptr)			free(ptr)
#endif

#ifndef MZ_REALLOC
	#define MZ_REALLOC(ptr, size)	mz_safe_realloc(ptr, size)
#endif

void* mz_safe_realloc(void* ptr, size_t size);
#endif // MUZZLE_CORE_MEMORY_H