#ifndef MUZZLE_CORE_TEXTURE_INTERNAL_H
#define MUZZLE_CORE_TEXTURE_INTERNAL_H

#include "../backend.h"

typedef GLuint mz_texture;

MZ_API mz_texture mz_load_texture(GLenum target, uint32_t wrap_s, uint32_t wrap_t, uint32_t filter_min, uint32_t filter_mag);
MZ_API void mz_generate_texture_mipmap(mz_texture texture, GLenum target);
MZ_API void mz_unload_texture(mz_texture* texture);
MZ_API void mz_unload_textures(mz_texture* textures, size_t size);

#endif // MUZZLE_CORE_TEXTURE_INTERNAL_H