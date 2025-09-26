#version 450
layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec4 aTint;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec2 aPivot;
layout (location = 4) in int aTexID;
layout (location = 5) in float aRotation;
layout (location = 6) in int aRenderOrder;

layout (location = 0) out vec4 vTint;
layout (location = 1) out vec2 vTexCoord;
layout (location = 2) out int vTexID;

uniform vec2 uViewportResolution;

void main()
{
	vTint = aTint / 255;
	vTexCoord = aTexCoord;
	vTexID = aTexID;

	float rotation = radians(aRotation);
	float c = cos(rotation);
	float s = sin(rotation);

	vec2 rotatedPosition = (mat2(c, -s, s, c) * (aPosition - aPivot)) + aPivot;

	vec2 ndcPos = (2.0 * rotatedPosition / uViewportResolution) - 1.0;
	ndcPos.y *= -1;

	gl_Position = vec4(ndcPos, 1 - (0.001 * aRenderOrder), 1.0);
}
