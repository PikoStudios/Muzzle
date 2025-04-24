#version 450
layout (location = 0) in vec2 vTexCoord;
layout (location = 0) out vec4 fFragColor;

layout (std430, binding = 1) readonly buffer bBuffer
{
    float data[];
};

uniform float uTime;

void main()
{
    int t = int(uTime) % data.length();
    fFragColor = vec4(data[t] / 8, data[t] / 4, data[t] / 2, 255);
}
