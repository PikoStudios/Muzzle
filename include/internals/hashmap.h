#ifndef MUZZLE_INTERNALS_HASHMAP_H
#define MUZZLE_INTERNALS_HASHMAP_H

// Muzzle Hashmap
// Internal usage only, this hashmap implementation does not cover many edge cases hence it should not be used without caution

#include "backend.h"
#include <stdint.h>

#define HM_ENTRY(k,v,f) (internals_hm_entry){k,v,f,NULL,NULL}

typedef void (*internals_hm_entry_free_func)(void*, void*);

// TODO: Specialize for string => int associations
typedef struct internals_hm_entry
{
	void* key;
	void* value;
	internals_hm_entry_free_func free;
	struct internals_hm_entry* next;
	struct internals_hm_entry* prev;
} internals_hm_entry;

typedef struct internals_hashmap
{
	internals_hm_entry* entries;
	uint32_t* indices;
	size_t capacity;
	size_t size;
} internals_hashmap;

MZ_API void internals_hm_init(internals_hashmap* hm, size_t capacity);
MZ_API void internals_hm_free(internals_hashmap* hm);

MZ_API mz_boolean internals_hm_put(internals_hashmap* hm, internals_hm_entry entry);
MZ_API void* internals_hm_get(internals_hashmap* hm, void* key);

#if 0
MZ_API mz_boolean internals_hm_remove(internals_hashmap* hm, void* key);
#endif

MZ_API mz_boolean internals_hm_contains(internals_hashmap* hm, void* key);

MZ_API void internals_hm_entries(internals_hashmap* hm, internals_hm_entry* out, size_t size);

#endif // MUZZLE_INTERNALS_HASHMAP_H
