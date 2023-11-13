#version 450 core

struct vertexOutput
{
    vec4 tint;
    vec2 textureCoordinate;
    float textureId;
    float tilingFactor;
};

layout (location = 0) in vertexOutput inputData;
layout (location = 0) out vec4 fragColor;

uniform sampler2D u_Textures[32];

void main()
{
    vec4 texture_color = inputData.tint;
    
    switch(int(inputData.textureId))
    {
        case 0: texture_color = texture_color * texture(u_Textures[0], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 1: texture_color = texture_color * texture(u_Textures[1], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 2: texture_color = texture_color * texture(u_Textures[2], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 3: texture_color = texture_color * texture(u_Textures[3], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 4: texture_color = texture_color * texture(u_Textures[4], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 5: texture_color = texture_color * texture(u_Textures[5], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 6: texture_color = texture_color * texture(u_Textures[6], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 7: texture_color = texture_color * texture(u_Textures[7], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 8: texture_color = texture_color * texture(u_Textures[8], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 9: texture_color = texture_color * texture(u_Textures[9], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 10: texture_color = texture_color * texture(u_Textures[10], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 11: texture_color = texture_color * texture(u_Textures[11], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 12: texture_color = texture_color * texture(u_Textures[12], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 13: texture_color = texture_color * texture(u_Textures[13], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 14: texture_color = texture_color * texture(u_Textures[14], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 15: texture_color = texture_color * texture(u_Textures[15], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 16: texture_color = texture_color * texture(u_Textures[16], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 17: texture_color = texture_color * texture(u_Textures[17], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 18: texture_color = texture_color * texture(u_Textures[18], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 19: texture_color = texture_color * texture(u_Textures[19], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 20: texture_color = texture_color * texture(u_Textures[20], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 21: texture_color = texture_color * texture(u_Textures[21], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 22: texture_color = texture_color * texture(u_Textures[22], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 23: texture_color = texture_color * texture(u_Textures[23], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 24: texture_color = texture_color * texture(u_Textures[24], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 25: texture_color = texture_color * texture(u_Textures[25], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 26: texture_color = texture_color * texture(u_Textures[26], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 27: texture_color = texture_color * texture(u_Textures[27], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 28: texture_color = texture_color * texture(u_Textures[28], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 29: texture_color = texture_color * texture(u_Textures[29], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 30: texture_color = texture_color * texture(u_Textures[30], inputData.textureCoordinate * inputData.tilingFactor); break;
        case 31: texture_color = texture_color * texture(u_Textures[31], inputData.textureCoordinate * inputData.tilingFactor); break;
        default: break;
    }

    if (texture_color.a == 0.0) discard;
    
    fragColor = texture_color;
}