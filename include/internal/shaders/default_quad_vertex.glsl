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

layout (location = 0) out vertexOutput outputData;

void main()
{
    outputData.tint = a_Tint;
    outputData.textureCoordinate = a_TextureCoordinate;
    outputData.textureId = a_TextureId;
    outputData.tilingFactor = a_TilingFactor;
    
    vec4 position = vec4(a_Position, 0.0, 1.0);
    gl_Position = position;
}