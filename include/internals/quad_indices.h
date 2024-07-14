#ifndef MUZZLE_INTERNALS_QUAD_INDICES_H
#define MUZZLE_INTERNALS_QUAD_INDICES_H

#include "../backend.h"
#include <stdint.h>

void internals_generate_quad_indices(GLuint* indices, uint32_t max_quads);

#endif // MUZZLE_INTERNALS_QUAD_INDICES_H
