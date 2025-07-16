#version 450
layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
layout (rgba32f, binding = 0) uniform image2D uOutputTexture;

uniform vec2 uScreenResolution;

void main()
{
	vec4 color = vec4(vec3(vec2(gl_GlobalInvocationID.xy) / uScreenResolution, 0.5), 1.0);
	imageStore(uOutputTexture, ivec2(gl_GlobalInvocationID.xy), color);
}
