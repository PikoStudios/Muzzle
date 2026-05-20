#ifndef MUZZLE_CORE_MEMORY_H
#define MUZZLE_CORE_MEMORY_H

#include <stdlib.h>
#include <string.h>

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

#ifndef MZ_COPY_STRING
	#if defined(_MSC_VER) || (defined(__STDC_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ == 1)
		#define MZ_COPY_STRING(dest, destsize, src) strcpy_s((dest), (destsize), (src))
	#else
		#define MZ_COPY_STRING(dest, destsize, src) snprintf((dest), (destsize), "%s", (src))
	#endif
#endif

void* __mz_memory_reallocate(void* ptr, size_t size);

#endif // MUZZLE_CORE_MEMORY_H
