#version 450
layout (location = 0) in vec4 vTint;
layout (location = 1) in vec2 vTexCoord;
layout (location = 2) in flat int vTexID;
layout (location = 3) in float vTilingFactor;

layout (location = 0) out vec4 fFragColor;
uniform vec2 uViewportResolution;
uniform int uRenderOrderMax;
layout (binding = 0) uniform sampler2D uTextures[32];

void main()
{
	fFragColor = vTint * texture(uTextures[vTexID], vTexCoord);
	if (fFragColor.a == 0.0)
	{
		discard;
	}
}
