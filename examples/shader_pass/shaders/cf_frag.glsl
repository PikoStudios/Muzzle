#version 450
layout (location = 0) in vec2 vTexCoord;
layout (location = 0) out vec4 fFragColor;

uniform sampler2D uScreenTexture;
uniform float uTime;

void main()
{
    fFragColor = texture(uScreenTexture, vTexCoord) * vec4(cos(uTime), sin(uTime), 1.0, 1.0);
}
