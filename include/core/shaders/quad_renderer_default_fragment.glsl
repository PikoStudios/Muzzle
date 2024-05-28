#version 450
layout (location = 0) in vec4 aTint;
layout (location = 0) out vec4 vFragColor;

void main()
{
	vFragColor = aTint;
}
