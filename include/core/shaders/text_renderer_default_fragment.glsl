#version 450
layout (location = 0) in vec4 vTint;
layout (location = 1) in vec2 vTexCoord;
layout (location = 2) in flat int vTextureIDX;

layout (location = 0) out vec4 fFragColor;

uniform sampler2DArray uGlyphs;

void main()
{
	vec4 glyph = vec4(1.0);
	glyph.w = texture(uGlyphs, vec3(vTexCoord.xy, vTextureIDX)).r;
	fFragColor = vTint * glyph;
	if (fFragColor.a == 0.0)
	{
		discard;
	}
}
