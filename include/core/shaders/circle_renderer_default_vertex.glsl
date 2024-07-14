#version 450
layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec2 aCenterPosition;
layout (location = 2) in vec4 aTint;
layout (location = 3) in float aRadius;
layout (location = 4) in int aRenderOrder;

layout (location = 0) out vec2 vScreenCenterPosition;
layout (location = 1) out vec4 vTint;
layout (location = 2) out flat float vRadiusSquared;

uniform vec2 uViewportResolution;
uniform int uRenderOrderMax;

void main()
{
	vTint = aTint / 255;
	vScreenCenterPosition = aCenterPosition;
	vRadiusSquared = aRadius * aRadius;
	vec2 ndcPos = (2.0 * aPosition / uViewportResolution) - 1.0;
	gl_Position = vec4(ndcPos.x, -ndcPos.y, float(uRenderOrderMax) / (uRenderOrderMax + aRenderOrder), 1.0);
}
