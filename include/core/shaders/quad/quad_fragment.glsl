#version 450
layout (location = 0) in vec4 vTint;
layout (location = 0) out vec4 fFragColor;

void main()
{
	fFragColor = vTint;
	if (fFragColor.a == 0.0)
	{
		discard;
	}
}
