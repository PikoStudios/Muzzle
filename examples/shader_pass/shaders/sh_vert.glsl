#version 450
#define SHEAR_MATRIX mat4(1.0, 0.5, 0.0, 0.0, 0.3, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0)

layout (location = 0) in vec2 aScreenCoord;
layout (location = 1) in vec2 aTexCoord;

layout (location = 0) out vec2 vTexCoord;

void main()
{
    vTexCoord = aTexCoord;
    gl_Position = SHEAR_MATRIX * vec4(aScreenCoord, 0.0, 1.0);
}
