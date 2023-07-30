#include "internal/core.default_shaders.internal.h"
#include "internal/shaders/default_quad_vertex.glsl.h"
#include "internal/shaders/default_quad_frag.glsl.h"

shader mz_load_default_shader_fragment(void)
{
    return load_shader_from_string((char*)(default_quad_frag_glsl), SHADER_FRAGMENT);
}

shader mz_load_default_shader_vertex(void)
{
    return load_shader_from_string((char*)(default_quad_vertex_glsl), SHADER_VERTEX);
}