#ifndef MUZZLE_INTERNALS_GL_CALLBACK_H
#define MUZZLE_INTERNALS_GL_CALLBACK_H

#include "../backend.h"

MZ_API void GLAPIENTRY internals_gl_debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, /* always null */ const void* userparam);

#endif // MUZZLE_INTERNALS_GL_CALLBACK_H
