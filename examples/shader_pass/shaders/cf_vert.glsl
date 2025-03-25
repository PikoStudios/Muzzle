#version 450
layout (location = 0) in vec2 aScreenCoord;
layout (location = 1) in vec2 aTexCoord;

layout (location = 0) out vec2 vTexCoord;

void main()
{
    vTexCoord = aTexCoord;
    gl_Position = vec4(aScreenCoord, 0.0, 1.0);
}
