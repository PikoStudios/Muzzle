#version 450
layout (location = 0) in vec2 vTexCoord;
layout (location = 0) out vec4 fFragColor;

uniform sampler2D uScreenTexture;

void main()
{
    fFragColor = texture(uScreenTexture, vTexCoord);
}
