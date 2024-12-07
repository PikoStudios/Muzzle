#include "internals/gl_callbacks.h"
#include "core/logging.h"

void GLAPIENTRY internals_gl_debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, /* always null */ const void* userparam)
{
	mz_log_status_formatted((type == GL_DEBUG_TYPE_ERROR) ? LOG_STATUS_ERROR : LOG_STATUS_DEBUG, "OpenGL Debug:\n\tType: 0x%x\n\tSeverity: 0x%x\n\tSource: %s\n\tMessage: %s", type, severity, MZ_GET_CURRENT_FUNCTION(), message);
}
