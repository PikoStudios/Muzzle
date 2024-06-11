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
    gl_Position = vec4(ndcPos.x, -ndcPos.y, (aRenderOrder - 1) / uRenderOrderMax, 1.0);
}
