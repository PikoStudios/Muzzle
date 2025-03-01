#include "internals/hashmap.h"
#include "core/logging.h"

#define FNV_OFFSET_BASIS 2166136261U
#define FNV_PRIME 16777619U

static uint32_t hm_hash(void* key)
{
	uintptr_t ptr = (uintptr_t)(key);
	const uint8_t* data = (const uint8_t*)(&ptr);
	uint32_t hash = FNV_OFFSET_BASIS;

	for (int i = 0; i < sizeof(ptr); i++)
	{
		hash ^= data[i];
		hash *= FNV_PRIME;
	}

	return hash;
}

void internals_hm_init(internals_hashmap* hm, size_t capacity)
{
	hm->entries = MZ_CALLOC(hm->capacity, sizeof(internals_hm_entry));
	hm->indices = MZ_CALLOC(hm->capacity, sizeof(uint32_t));
	hm->capacity = capacity;
	hm->size = 0;

	if (hm->entries == NULL || hm->indices == NULL)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Failed to initialize memory for hashmap");
	}
}

void internals_hm_free(internals_hashmap* hm)
{
	for (int i = 0; i < hm->capacity; i++)
	{
		internals_hm_entry* entry = &hm->entries[hm->indices[i]];

		while (entry != NULL)
		{
			if (entry->free != NULL)
			{
				entry->free(entry->key, entry->value);
			}

			internals_hm_entry* curr = entry;
			entry = entry->next;
			curr->next = NULL;

			// Free ourselves if not a head entry
			if (curr->prev != NULL)
			{
				curr->prev = NULL;
				MZ_FREE(curr);
			}
		}
	}

	MZ_FREE(hm->entries);
	MZ_FREE(hm->indices);

	hm->entries = NULL;
	hm->indices = NULL;
	hm->capacity = 0;
}

mz_boolean internals_hm_put(internals_hashmap* hm, internals_hm_entry entry)
{
	if (hm->size == hm->capacity)
	{
		return MUZZLE_FALSE;
	}
	
	uint32_t hash = hm_hash(entry.key) % hm->capacity;
	hm->indices[hm->size] = hash;
	hm->size++;

	if (hm->entries[hash].key == NULL)
	{
		hm->entries[hash] = entry;
		hm->entries[hash].next = NULL;
		hm->entries[hash].prev = NULL;
		return MUZZLE_TRUE;
	}

	internals_hm_entry* ptr = &hm->entries[hash];

	// Traverse to tail of linked list
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}

	ptr->next = MZ_MALLOC(sizeof(internals_hm_entry));
	*ptr->next = entry;
	
	ptr->next->prev = ptr;
	ptr->next->next = NULL;

	return MUZZLE_TRUE;
}

static inline internals_hm_entry* hm_get(internals_hashmap* hm, void* key)
{
	uint32_t hash = hm_hash(key) % hm->capacity;
	internals_hm_entry* entry = &hm->entries[hash];

	while (entry->key != key)
	{
		if (entry->next == NULL)
		{
			return NULL;
		}
		
		entry = entry->next;
	}

	return entry;
}

void* internals_hm_get(internals_hashmap* hm, void* key)
{
	internals_hm_entry* entry = hm_get(hm, key);
	return entry != NULL ? entry->value : NULL;
}

#if 0
// Not complete
mz_boolean internals_hm_remove(internals_hashmap* hm, void* key)
{
	internals_hm_entry* entry = hm_get(hm, key);

	if (entry == NULL)
	{
		return MUZZLE_FALSE;
	}

	// TODO: Update hm->indices
	hm->size--;

	if (entry->prev == NULL)
	{
		entry->key = NULL;
		entry->value = NULL;
		
		if (entry->next != NULL)
		{
			entry->key = entry->next->key;
			entry->value = entry->next->value;
			entry->next = entry->next->next;

			entry->next->key = NULL;
			entry->next->value = NULL;
			entry->next->next = NULL;
			entry->next->prev = NULL;

			MZ_FREE(entry->next);
		}
		
		return MUZZLE_TRUE;
	}

	entry->prev->next = entry->next;
	entry->next->prev = entry->prev;

	if (entry->free != NULL)
	{
		entry->free(entry->key, entry->value);
	}
	
	entry->prev = NULL;
	entry->next = NULL;
	entry->key = NULL;
	entry->value = NULL;

	MZ_FREE(entry);

	return MUZZLE_TRUE;
}
#endif

mz_boolean internals_hm_contains(internals_hashmap* hm, void* key)
{
	return hm_get(hm, key) != NULL;
}

void internals_hm_entries(internals_hashmap* hm, internals_hm_entry* out, size_t size)
{
	for (int i = 0; i < size && i < hm->size; i++)
	{
		out[i] = hm->entries[hm->indices[i]];
	}
}
