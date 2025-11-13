#ifndef MUZZLE_GPU_BUFFER_H
#define MUZZLE_GPU_BUFFER_H

#include "../../backend.h"
#include <stdint.h>

typedef enum
{
    GPU_BUFFER_USAGE_STATIC = 0,
    GPU_BUFFER_USAGE_DYNAMIC = 1,
    GPU_BUFFER_USAGE_STREAM = 2,
} mz_gpu_buffer_usage;

typedef struct mz_gpu_buffer
{
	uintptr_t handle;
	uintptr_t impl_handle;
	size_t size;
	mz_gpu_buffer_usage usage;
} mz_gpu_buffer;

#endif // MUZZLE_GPU_BUFFER_H
