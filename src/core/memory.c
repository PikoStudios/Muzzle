#include "core/memory.h"

void* __mz_memory_reallocate(void* ptr, size_t size)
{
	void* tmp = realloc(ptr, size);
	
	if (tmp == NULL)
	{
		MZ_FREE(ptr);
	}
	
	return tmp;
}
