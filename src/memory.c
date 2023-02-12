#include "memory.h"

void* mz_safe_realloc(void* ptr, size_t size)
{
	void* temp = realloc(ptr, size);
	
	if (temp == NULL)
	{
		MZ_FREE(ptr);
		return NULL;
	}
	
	return temp;
}