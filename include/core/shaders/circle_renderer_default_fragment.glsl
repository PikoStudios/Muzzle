#version 450
#define SQUARE(n) (n)*(n)
layout (location = 0) in vec2 vScreenCenterPosition;
layout (location = 1) in vec4 vTint;
layout (location = 2) in flat float vRadiusSquared;

layout (location = 0) out vec4 fFragColor;

uniform vec2 uViewportResolution;

void main()
{
	fFragColor = vTint;
	if (fFragColor.a == 0.0 || SQUARE(gl_FragCoord.x-vScreenCenterPosition.x) + SQUARE(uViewportResolution.y - gl_FragCoord.y - vScreenCenterPosition.y) > vRadiusSquared)
	{
		discard;
	}
}
