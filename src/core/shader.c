#include "core/shader.h"
#include "backend.h"
#include "core/drawing.h"
#include "core/logging.h"
#include "internals/file_helper.h"

static void verify_compile_status(const char* on_error_msg, GLuint id)
{
	MZ_TRACK_FUNCTION();

	GLint s = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &s);

	if (s != GL_TRUE)
	{
		GLsizei length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		GLchar log[length];
		glGetShaderInfoLog(id, length, NULL, log);

		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "%s%s", on_error_msg, log);
	}
}

mz_shader mz_create_shader(const char* vertex, const char* fragment, mz_shader_type type)
{
	MZ_TRACK_FUNCTION();

	GLuint vid = glCreateShader(GL_VERTEX_SHADER);
	GLuint fid = glCreateShader(GL_FRAGMENT_SHADER);

	if (vid == 0 || fid == 0)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Could not create shader");
	}

	glShaderSource(vid, 1, &vertex, NULL);
	glCompileShader(vid);
	verify_compile_status("Vertex shader failed to compile, more info:\n\t", vid);

	glShaderSource(fid, 1, &fragment, NULL);
	glCompileShader(fid);
	verify_compile_status("Fragment shader failed to compile, more info:\n\t", fid);

	GLuint pid = glCreateProgram();
	glAttachShader(pid, vid);
	glAttachShader(pid, fid);
	glLinkProgram(pid);

	GLint s = 0;
	glGetProgramiv(pid, GL_LINK_STATUS, &s);

	if (s != GL_TRUE)
	{
		GLsizei length = 0;
		glGetProgramiv(pid, GL_INFO_LOG_LENGTH, &length);

		GLchar log[length];
		glGetProgramInfoLog(pid, length, NULL, log);

		glDeleteShader(vid);
		glDeleteShader(fid);
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Shader failed to link, more info:\n\t%s", log);
	}

	glDetachShader(pid, vid);
	glDetachShader(pid, fid);
	glDeleteShader(vid);
	glDeleteShader(fid);

	return (mz_shader)
	{
		.pid = pid,
		.type = type
	};
}
mz_shader mz_load_shader(const char* vertex_filepath, const char* fragment_filepath, mz_shader_type type)
{
	MZ_TRACK_FUNCTION();

	FILE* file;

	char* vertex_source = internals_read_file(&file, vertex_filepath, "Could not read vertex shader file", "Could not allocate memory for vertex shader string buffer");
	char* fragment_source = internals_read_file(&file, fragment_filepath, "Could not read fragment shader file", "Could not allocate memory for fragment shader string buffer");
	mz_shader id = mz_create_shader(vertex_source, fragment_source, type);

	MZ_FREE(vertex_source);
	MZ_FREE(fragment_source);

	return id;
}

MZ_API void mz_use_shader_pass(mz_applet* applet, mz_shader shader)
{
	MZ_TRACK_FUNCTION();

	MZ_ASSERT_DETAILED(shader.type == SHADER_TYPE_PASS, "Passed shader should be a shader pass");

	if (applet->shader_passes_len >= MUZZLE_MAX_SHADER_PASSES)
	{
		mz_log_status(LOG_STATUS_ERROR, "Maximum concurrent shader passes reached...");
		return;
	}

	applet->shader_passes[applet->shader_passes_len++] = shader.pid;

	glBindFramebuffer(GL_FRAMEBUFFER, applet->framebuffer_buffers[0]);
}

void mz_begin_shader(mz_applet* applet, mz_shader shader)
{
	MZ_TRACK_FUNCTION();

	switch (shader.type)
	{
		case SHADER_TYPE_PASS:
			mz_log_status(LOG_STATUS_ERROR, "mz_begin_shader called on shader pass, please use `mz_use_shader_pass`");
			break;

		case SHADER_TYPE_DIRECT_CIRCLE:
			applet->circle_renderer.shader_id = shader.pid;
			break;

		case SHADER_TYPE_DIRECT_QUAD:
			applet->quad_renderer.shader_id = shader.pid;
			break;

		case SHADER_TYPE_DIRECT_SPRITE:
			applet->sprite_renderer.shader_id = shader.pid;
			break;

		case SHADER_TYPE_DIRECT_TEXT:
			applet->text_renderer.shader_id = shader.pid;
			break;
	}
}

void mz_end_shader(mz_applet* applet, mz_shader shader)
{
	switch (shader.type)
	{
		case SHADER_TYPE_PASS:
			mz_log_status(LOG_STATUS_ERROR, "mz_end_shader called on a shader pass");
			break;

		case SHADER_TYPE_DIRECT_CIRCLE:
			applet->circle_renderer.shader_id = applet->circle_renderer.default_shader_id;
			break;


		case SHADER_TYPE_DIRECT_QUAD:
			applet->quad_renderer.shader_id = applet->quad_renderer.default_shader_id;
			break;


		case SHADER_TYPE_DIRECT_SPRITE:
			applet->sprite_renderer.shader_id = applet->sprite_renderer.default_shader_id;
			break;


		case SHADER_TYPE_DIRECT_TEXT:
			applet->text_renderer.shader_id = applet->text_renderer.default_shader_id;
			break;
	}
}


MZ_API void mz_upload_uniform_int(mz_shader shader, const char* uniform, int value)
{
	GLuint loc = glGetUniformLocation(shader.pid, uniform);
	glUseProgram(shader.pid);
	glUniform1i(loc, value);
}

MZ_API void mz_upload_uniform_float(mz_shader shader, const char* uniform, float value)
{
	GLuint loc = glGetUniformLocation(shader.pid, uniform);
	glUseProgram(shader.pid);
	glUniform1f(loc, value);
}

MZ_API void mz_upload_uniform_vec2(mz_shader shader, const char* uniform, mz_vec2 value)
{
	GLuint loc = glGetUniformLocation(shader.pid, uniform);
	glUseProgram(shader.pid);
	glUniform2f(loc, value.x, value.y);
}

MZ_API void mz_upload_uniform_vec3(mz_shader shader, const char* uniform, mz_vec3 value)
{
	GLuint loc = glGetUniformLocation(shader.pid, uniform);
	glUseProgram(shader.pid);
	glUniform3f(loc, value.x, value.y, value.z);
}

MZ_API void mz_upload_uniform_vec4(mz_shader shader, const char* uniform, mz_vec4 value)
{
	GLuint loc = glGetUniformLocation(shader.pid, uniform);
	glUseProgram(shader.pid);
	glUniform4f(loc, value.x, value.y, value.z, value.w);
}

MZ_API void mz_upload_uniform_mat3(mz_shader shader, const char* uniform, const float* matrix)
{
	GLuint loc = glGetUniformLocation(shader.pid, uniform);
	glUseProgram(shader.pid);
	glUniformMatrix4fv(loc, 1, GL_FALSE, matrix);
}

MZ_API void mz_upload_uniform_mat4(mz_shader shader, const char* uniform, const float* matrix)
{
	GLuint loc = glGetUniformLocation(shader.pid, uniform);
	glUseProgram(shader.pid);
	glUniformMatrix4fv(loc, 1, GL_FALSE, matrix);
}
