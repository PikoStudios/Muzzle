#version 450
layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec4 aTint;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in int aTexID;
layout (location = 4) in float aTilingFactor;
layout (location = 5) in int aRenderOrder;

layout (location = 0) out vec4 vTint;
layout (location = 1) out vec2 vTexCoord;
layout (location = 2) out int vTexID;
layout (location = 3) out float vTilingFactor;

uniform vec2 uViewportResolution;
uniform int uRenderOrderMax;

void main()
{
	vTint = aTint / 255;
	vTexCoord = aTexCoord;
	vTexID = aTexID;
	vTilingFactor = aTilingFactor;
	vec2 ndcPos = (2.0 * aPosition / uViewportResolution) - 1.0;
	gl_Position = vec4(ndcPos.x, -ndcPos.y, float(uRenderOrderMax) / (uRenderOrderMax + aRenderOrder), 1.0);
}
