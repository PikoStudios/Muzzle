#version 450
layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec4 aTint;
layout (location = 2) in int aRenderOrder;

layout (location = 0) out vec4 vTint;
uniform vec2 uViewportResolution;
uniform int uRenderOrderMax;

void main()
{
    vTint = aTint / 255;
    vec2 ndcPos = (2.0 * aPosition / uViewportResolution) - 1.0;
    // TODO: Fix this 1 - (0.001 * ...), it only allows for 999 quads at once
    gl_Position = vec4(ndcPos.x, -ndcPos.y,1 - (0.001 * aRenderOrder), 1.0);
}
