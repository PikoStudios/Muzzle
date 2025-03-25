#version 450
#define GRAYSCALE_SCALAR vec3(0.2126, 0.7162, 0.0722)

layout (location = 0) in vec2 vTexCoord;
layout (location = 0) out vec4 fFragColor;

uniform sampler2D uScreenTexture;

void main()
{
    float grayscale = dot(texture(uScreenTexture, vTexCoord).xyz * GRAYSCALE_SCALAR, vec3(1.0));
    fFragColor = vec4(vec3(grayscale), 1.0);
}
