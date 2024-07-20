#version 450
layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in int aTextureIDX;

layout (location = 0) out vec4 vTint;
layout (location = 1) out vec2 vTexCoords;
layout (location = 2) out int vTextureIDX;

uniform vec2 uViewportResolution
uniform vec4 uTint;
uniform int uRenderOrder;

void main()
{
	vTint = aTint / 255;
	vTextureIDX = aTextureIDX;
	vTexCoords = aTexCoords;
	vec2 ndcPos = (2.0 * aPosition / uViewportResolution) - 1.0;
	gl_Position = vec4(ndcPos.x, -ndcPos.y, 1 - (0.001 * uRenderOrder), 1.0);
}
