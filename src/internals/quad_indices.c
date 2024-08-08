#include "internals/quad_indices.h"

void internals_generate_quad_indices(GLuint* indices, uint32_t max_quads)
{
	for (int i = 0, offset = 0; i < max_quads * 6; i += 6, offset += 4)
	{
		// Triangle 1
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 3;
		indices[i + 2] = offset + 2;

		// Triangle 2
		indices[i + 3] = offset + 0;
		indices[i + 4] = offset + 1;
		indices[i + 5] = offset + 3;
	}
}
