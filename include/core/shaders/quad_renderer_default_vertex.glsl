#version 450
layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec4 aTint;

layout (location = 0) out vec4 vTint;
uniform vec2 uViewportResolution;

void main()
{
    vTint = aTint / 255;
    vec2 ndcPos = (2.0 * aPosition / uViewportResolution) - 1.0;
    gl_Position = vec4(ndcPos.x, -ndcPos.y, 0.0, 1.0);
}
