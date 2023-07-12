#version 450 core
layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec4 a_Tint;
layout (location = 2) in vec2 a_TextureCoordinate;
layout (location = 3) in float a_TextureId;
layout (location = 4) in float a_TilingFactor;

uniform mat4 u_ViewProjectionMatrix;

struct vertexOutput
{
    vec4 tint;
    vec2 textureCoordinate;
    float textureId;
    float tilingFactor;
};

layout (location = 0) out struct vertexOutput output;

void main()
{
    output.tint = a_Tint;
    output.textureCoordinate = a_TextureCoordinate;
    output.textureId = a_TextureId;
    output.tilingFactor = a_TilingFactor;
    
    gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
}