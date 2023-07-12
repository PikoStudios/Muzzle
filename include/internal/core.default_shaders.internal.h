#ifndef MUZZLE_CORE_DEFAULT_SHADERS_H
#define MUZZLE_CORE_DEFAULT_SHADERS_H

#include "../backend.h"
#include "../core/Shader.h"

MZ_API shader mz_load_default_shader_fragment(void);
MZ_API shader mz_load_default_shader_vertex(void);

#endif // MUZZLE_CORE_DEFAULT_SHADERS_H