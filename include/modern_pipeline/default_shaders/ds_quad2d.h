#pragma once

#define MUZZLE_DEFAULT_SHADER_QUAD_2D_VERTEX "#version 450 core\n" \
"layout (location = 0) in vec3 a_Position;\n" \
"layout (location = 1) in vec4 a_ColorDrawn;\n" \
"layout (location = 2) in vec2 a_TexCoords;\n" \
"layout (location = 3) in float a_TexID;\n" \
"struct VertexOutputData\n" \
"{\n" \
"	vec4 ColorDrawn;\n" \
"	vec2 TexCoords;\n" \
"	float TexID;\n" \
"};\n" \
"out VertexOutputData OutputData;\n" \
"void main()\n" \
"{\n" \
"	OutputData.ColorDrawn = a_ColorDrawn;\n" \
"	OutputData.TexCoords = a_TexCoords;\n" \
"	OutputData.TexID = a_TexID;\n" \
"	ViewProjection = 1;\n" \
"	gl_Position = ViewProjection * vec4(a_Position, 1.0);\n" \
"}\n\0"

#define MUZZLE_DEFAULT_SHADER_QUAD_2D_FRAGMENT "#version 450 core\n" \
"struct VertexOutputData\n" \
"{\n" \
"	vec4 ColorDrawn;\n" \
"	vec2 TexCoords;\n" \
"	float TexID;\n" \
"};\n" \
"in VertexOutputData InputData;\n" \
"out vec4 f_Color;\n" \
"layout (binding = 0) uniform sampler2D u_Textures[32];\n" \
"void main()\n" \
"{\n" \
"	vec4 textureColorDrawn = InputData.ColorDrawn;\n" \
"	int textureIndex = int(InputData.TexID);\n" \
"	if (textureIndex < 32)\n" \
"	{\n" \
"		textureColorDrawn *= texture(u_Textures[textureIndex], InputData.TexCoords);\n" \
"	}\n" \
"	f_Color = textureColorDrawn;\n" \
"}\n\0"