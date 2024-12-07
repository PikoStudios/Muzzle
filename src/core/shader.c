#include "core/shader.h"
#include "core/logging.h"
#include "internals/file_helper.h"
#include "internals/todo.h"
#include <stdio.h>

static void handle_compile_status(const char* msg, GLuint id)
{
	MZ_TRACK_FUNCTION();

	GLint s = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &s);

	if (s != GL_TRUE)
	{
		GLsizei info_log_length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_log_length);

		GLchar info_log[info_log_length];
		glGetShaderInfoLog(id, info_log_length, NULL, info_log);

		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "%s%s", msg, info_log);
	}
}

mz_shader mz_create_shader(const char* vertex_src, const char* fragment_src, mz_shader_target target)
{
	MZ_TRACK_FUNCTION();

	GLuint vid = glCreateShader(GL_VERTEX_SHADER);
	GLuint fid = glCreateShader(GL_FRAGMENT_SHADER);

	if (vid == 0 || fid == 0)
	{
		// TODO: Give reason
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Could not create shader");
	}

	glShaderSource(vid, 1, &vertex_src, NULL);
	glCompileShader(vid);
	handle_compile_status("Vertex shader failed to compile, more info:\n\t", vid);

	glShaderSource(fid, 1, &fragment_src, NULL);
	glCompileShader(fid);
	handle_compile_status("Fragment shader failed to compile, more info:\n\t", fid);

	GLuint pid = glCreateProgram();
	glAttachShader(pid, vid);
	glAttachShader(pid, fid);
	glLinkProgram(pid);

	GLint s = 0;
	glGetProgramiv(pid, GL_LINK_STATUS, &s);

	if (s != GL_TRUE)
	{
		GLsizei info_log_length = 0;
		glGetProgramiv(pid, GL_INFO_LOG_LENGTH, &info_log_length);

		GLchar info_log[info_log_length];
		glGetProgramInfoLog(pid, info_log_length, NULL, info_log);

		glDeleteShader(vid);
		glDeleteShader(fid);
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Shader failed to link, more info:\n\t%s", info_log);
	}

	// TODO: debug and check
	glDetachShader(pid, vid);
	glDetachShader(pid, fid);
	glDeleteShader(vid);
	glDeleteShader(fid);
	
	return (mz_shader)
	{
		.pid = pid,
		.target = target
	};
}

int mz_create_shaders(mz_shader* out, size_t out_len, const char** vertex_srcs, size_t vs_len, const char** fragment_srcs, size_t fs_len, mz_shader_target target)
{	
	int i;
	int min_len = (vs_len < fs_len) ? vs_len : fs_len;
	
	if (out == NULL)
	{
		return min_len; // Return min of vs_len and fs_len
	}
	
	for (i = 0; i < min_len; i++)
	{
		if (i >= out_len)
		{
			break;
		}

		out[i] = mz_create_shader(vertex_srcs[i], fragment_srcs[i], target);
	}

	return i;
}

mz_shader mz_load_shader(const char* vertex_filepath, const char* fragment_filepath, mz_shader_target target)
{
	FILE* file;
	
	char* vertex_source = internals_read_file(&file, vertex_filepath, "Could not read vertex shader file", "Could not allocate memory for vertex shader string buffer");
	char* fragment_source = internals_read_file(&file, fragment_filepath, "Could not read fragment shader file", "Could not allocate memory for fragment shader string buffer");
	mz_shader id = mz_create_shader(vertex_source, fragment_source, target);
	
	MZ_FREE(vertex_source);
	MZ_FREE(fragment_source);

	return id;
}

int mz_load_shaders(mz_shader* out, size_t out_len, const char** vertex_filepaths, size_t vf_len, const char** fragment_filepaths, size_t ff_len, mz_shader_target target)
{
	
	int i;
	int min_len = (vf_len < ff_len) ? vf_len : ff_len;
	
	if (out == NULL)
	{
		return min_len; // Return min of vs_len and fs_len
	}
	
	for (i = 0; i < min_len; i++)
	{
		if (i >= out_len)
		{
			break;
		}

		out[i] = mz_load_shader(vertex_filepaths[i], fragment_filepaths[i], target);
	}

	return i;
}

void mz_use_shader(mz_applet* applet, mz_shader shader)
{
	switch (shader.target)
	{
	case SHADER_TARGET_QUAD:
		applet->quad_renderer.shader_id = shader.pid;
		break;

	default:
		mz_log_status_formatted(LOG_STATUS_ERROR, "Unknown shader target '%d'", shader.target);
		break;
	}
}

void mz_use_shaders(mz_applet* applet, mz_shader* shaders, size_t shaders_len)
{
	// TODO: Multipass rendering
	TODO();
}

void mz_unload_shader(mz_shader shader)
{
	MZ_TRACK_FUNCTION();
	glDeleteProgram(shader.pid);
}

void mz_unload_shaders(mz_shader* shaders, size_t len)
{
	MZ_TRACK_FUNCTION();

	for (int i = 0; i < len; i++)
	{
		glDeleteProgram(shaders[i].pid);
	}
}
