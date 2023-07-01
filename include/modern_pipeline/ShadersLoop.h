#pragma once
#include "../backend.h"
#include "../core/Applet.h"
#include "../core/Batcher.h"
#include "../modern_pipeline/Shaders.h"

enum _mz_geometry_type
{
    GEOMETRY_QUAD = 0,
    GEOMETRY_CIRCLE = 1,
    GEOMETRY_LINE = 2,
    GEOMETRY_ALL = 3
};

typedef enum _mz_geometry_type geometry_type;

MZ_API void begin_shader(Applet* applet, shader_program shader, geometry_type type);
MZ_API void end_shader(Applet* Applet, shader_program shader, geometry_type type);