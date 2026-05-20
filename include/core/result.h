#ifndef MUZZLE_CORE_RESULT_H
#define MUZZLE_CORE_RESULT_H

#include "../backend.h"
#include <stdint.h>
#include <stdnoreturn.h>

typedef uintptr_t mz_result;

#define MZ_RESULT_OK(ptr)	 	((uintptr_t)((ptr)))
#define MZ_RESULT_ERROR(err) 	(((uintptr_t)((err)) << 1) | 1)
#define MZ_RESULT_IS_ERROR(r)	(((r) & 1))
#define MZ_RESULT_IS_OK(r)	 	(!((r) & 1))

// When a null pointer is passed as input, it returns the error, otherwise an OK result
#define MZ_RESULT_OF(ptr, err) (((ptr) == NULL) ? ((uintptr_t)((err) << 1) | 1) : (uintptr_t)((ptr)))

#define MZ_UNWRAP_RESULT_DANGEROUSLY(r) ((void*)(r))
#define MZ_UNWRAP_RESULT(r) (((r) & 1) ? __mz_unwrap_error(__func__, __FILE__, __LINE__) : (void*)(r))
#define MZ_GET_RESULT_ERROR(r) ((int)(v >> 1))

// Purely for documentation
#define MZ_RETURNS_RESULT(T,E)

MZ_API noreturn void* __mz_unwrap_error(const char* func, const char* file, int line); 

#endif // MUZZLE_CORE_RESULT_H
