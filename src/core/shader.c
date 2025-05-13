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

mz_shader_pipeline mz_create_shader_pipeline(mz_shader_pipeline_descriptor* descriptor)
{
	MZ_TRACK_FUNCTION();

	GLuint vid = glCreateShader(GL_VERTEX_SHADER);
	GLuint fid = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint gid = 0;

	if (vid == 0 || fid == 0)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Could not create shader");
	}

	char* vertex_source = (char*)(descriptor->vertex.source);
	char* fragment_source = (char*)(descriptor->fragment.source);
	char* geometry_source = (char*)(descriptor->geometry.source);

	if (descriptor->vertex.source_type == SHADER_COMPONENT_SOURCE_TYPE_FILEPATH)
	{
		FILE* file;
		vertex_source = internals_read_file(&file, vertex_source, "Failed to open vertex shader file", "Failed to allocate vertex shader string buffer");
	}

	if (descriptor->fragment.source_type == SHADER_COMPONENT_SOURCE_TYPE_FILEPATH)
	{
		FILE* file;
		fragment_source = internals_read_file(&file, fragment_source, "Failed to open fragment shader file", "Failed to allocate fragment shader string buffer");
	}

	if (geometry_source != NULL)
	{
		gid = glCreateShader(GL_GEOMETRY_SHADER);

		if (gid == 0)
		{
			mz_log_status(LOG_STATUS_FATAL_ERROR, "Could not create shader");
		}

		if (descriptor->geometry.source_type == SHADER_COMPONENT_SOURCE_TYPE_FILEPATH)
		{
			FILE* file;
			geometry_source = internals_read_file(&file, geometry_source, "Failed to open geometry shader file", "Failed to allocate geometry shader string buffer");
		}
	}

	// Qualifer warning so this is necessary
	const char* vertex = vertex_source;
	const char* fragment = fragment_source;
	const char* geometry = geometry_source;

	glShaderSource(vid, 1, &vertex, NULL);
	glCompileShader(vid);
	verify_compile_status("Vertex shader failed to compile, more info:\n\t%s", vid);

	glShaderSource(fid, 1, &fragment, NULL);
	glCompileShader(fid);
	verify_compile_status("Fragment shader failed to compile, more info:\n\t%s", fid);

	GLuint pid = glCreateProgram();
	glAttachShader(pid, vid);
	glAttachShader(pid, fid);

	if (gid != 0)
	{
		glShaderSource(gid, 1, &geometry, NULL);
		glCompileShader(gid);
		verify_compile_status("Geometry shader failed to compile, more info:\n\t%s", gid);
		
		glAttachShader(pid, gid);
	}

	glLinkProgram(pid);

	GLint status = 0;
	glGetProgramiv(pid, GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		GLsizei length = 0;
		glGetProgramiv(pid, GL_INFO_LOG_LENGTH, &length);

		GLchar log[length];
		glGetProgramInfoLog(pid, length, NULL, log);

		glDeleteShader(vid);
		glDeleteShader(fid);

		if (gid != 0)
		{
			glDeleteShader(gid);
		}

		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Shader failed to link, more info:\n\t%s", log);
	}

	glDetachShader(pid, vid);
	glDetachShader(pid, fid);
	glDeleteShader(vid);
	glDeleteShader(fid);

	if (gid != 0)
	{
		glDetachShader(pid, gid);
		glDeleteShader(gid);
	}

	// Create Vertex buffers
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * descriptor->vertex.vertices_size, descriptor->vertex.vertices, GL_DYNAMIC_DRAW);

	for (mz_shader_component_vertex_attribute* attr = descriptor->vertex.attributes; attr != NULL; attr = attr->next)
	{
		glEnableVertexArrayAttrib(vao, attr->index);
		glVertexAttribPointer(attr->index, attr->size, GL_FLOAT, attr->normalized, attr->stride, (GLvoid*)(attr->offset));
	}

	return (mz_shader_pipeline)
	{
		.pid = pid,
		.vao = vao,
		.vbo = vbo,
		.primitive_type = descriptor->vertex.primitive_type
	};
}

void mz_draw_shader_pipeline(mz_shader_pipeline pipeline, float* vertices, size_t vertices_size, int start, int end)
{
	glUseProgram(pipeline.pid);
	glBindVertexArray(pipeline.vao);
	glBindBuffer(GL_ARRAY_BUFFER, pipeline.vbo);

	if (vertices != NULL)
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * vertices_size, vertices);
	}

	glDrawArrays(pipeline.primitive_type, start, end);
}

void mz_unload_shader_pipeline(mz_shader_pipeline* pipeline)
{
	glDeleteProgram(pipeline->pid);
	glDeleteBuffers(1, &pipeline->vbo);
	glDeleteVertexArrays(1, &pipeline->vao);

	pipeline->pid = 0;
	pipeline->vao = 0;
	pipeline->vbo = 0;
}

void mz_use_shader_pass(mz_applet* applet, mz_shader shader)
{
	MZ_TRACK_FUNCTION();

	MZ_ASSERT_DETAILED(shader.type == SHADER_TYPE_PASS, "Passed shader should be a shader pass");

	if (applet->shader_passes_len >= MUZZLE_MAX_SHADER_PASSES)
	{
		mz_log_status(LOG_STATUS_ERROR, "Maximum concurrent shader passes reached...");
		return;
	}

	applet->shader_passes[applet->shader_passes_len++] = shader.pid;

	glUseProgram(shader.pid);

	glBindFramebuffer(GL_FRAMEBUFFER, applet->framebuffer.fbos[0]);
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

void mz_unload_shader(mz_shader shader)
{
	glDeleteProgram(shader.pid);
}

void mz_upload_uniform_int(mz_shader shader, const char* uniform, int value)
{
	MZ_TRACK_FUNCTION();

	GLuint loc = glGetUniformLocation(shader.pid, uniform);
	glUseProgram(shader.pid);

	if (loc == -1)
	{
		mz_log_status_formatted(LOG_STATUS_ERROR, "Uniform '%s' not found in shader %d", uniform, shader.pid);
	}

	glUniform1i(loc, value);
}

void mz_upload_uniform_float(mz_shader shader, const char* uniform, float value)
{
	MZ_TRACK_FUNCTION();

	GLuint loc = glGetUniformLocation(shader.pid, uniform);
	glUseProgram(shader.pid);

	if (loc == -1)
	{
		mz_log_status_formatted(LOG_STATUS_ERROR, "Uniform '%s' not found in shader %d", uniform, shader.pid);
	}

	glUniform1f(loc, value);
}

void mz_upload_uniform_vec2(mz_shader shader, const char* uniform, mz_vec2 value)
{
	MZ_TRACK_FUNCTION();

	GLuint loc = glGetUniformLocation(shader.pid, uniform);
	glUseProgram(shader.pid);

	if (loc == -1)
	{
		mz_log_status_formatted(LOG_STATUS_ERROR, "Uniform '%s' not found in shader %d", uniform, shader.pid);
	}

	glUniform2f(loc, value.x, value.y);
}

void mz_upload_uniform_vec3(mz_shader shader, const char* uniform, mz_vec3 value)
{
	MZ_TRACK_FUNCTION();

	GLuint loc = glGetUniformLocation(shader.pid, uniform);
	glUseProgram(shader.pid);

	if (loc == -1)
	{
		mz_log_status_formatted(LOG_STATUS_ERROR, "Uniform '%s' not found in shader %d", uniform, shader.pid);
	}

	glUniform3f(loc, value.x, value.y, value.z);
}

void mz_upload_uniform_vec4(mz_shader shader, const char* uniform, mz_vec4 value)
{
	MZ_TRACK_FUNCTION();

	GLuint loc = glGetUniformLocation(shader.pid, uniform);
	glUseProgram(shader.pid);

	if (loc == -1)
	{
		mz_log_status_formatted(LOG_STATUS_ERROR, "Uniform '%s' not found in shader %d", uniform, shader.pid);
	}

	glUniform4f(loc, value.x, value.y, value.z, value.w);
}

void mz_upload_uniform_mat3(mz_shader shader, const char* uniform, const float* matrix)
{
	MZ_TRACK_FUNCTION();

	GLuint loc = glGetUniformLocation(shader.pid, uniform);
	glUseProgram(shader.pid);

	if (loc == -1)
	{
		mz_log_status_formatted(LOG_STATUS_ERROR, "Uniform '%s' not found in shader %d", uniform, shader.pid);
	}

	glUniformMatrix4fv(loc, 1, GL_FALSE, matrix);
}

void mz_upload_uniform_mat4(mz_shader shader, const char* uniform, const float* matrix)
{
	MZ_TRACK_FUNCTION();

	GLuint loc = glGetUniformLocation(shader.pid, uniform);
	glUseProgram(shader.pid);

	if (loc == -1)
	{
		mz_log_status_formatted(LOG_STATUS_ERROR, "Uniform '%s' not found in shader %d", uniform, shader.pid);
	}

	glUniformMatrix4fv(loc, 1, GL_FALSE, matrix);
}

mz_shader_buffer mz_create_shader_buffer(int index, void* data, size_t size)
{
	MZ_TRACK_FUNCTION();

	GLuint ssbo;

	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	return (mz_shader_buffer)
	{
		.id = ssbo,
		.index = index
	};
}

void mz_upload_shader_buffer(mz_shader_buffer buffer, intptr_t offset, void* data, size_t size)
{
	MZ_TRACK_FUNCTION();

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer.id);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void mz_realloc_shader_buffer(mz_shader_buffer buffer, void* data, size_t size)
{
	MZ_TRACK_FUNCTION();

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer.id);
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, buffer.index, buffer.id);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void mz_unload_shader_buffer(mz_shader_buffer buffer)
{
	MZ_TRACK_FUNCTION();

	glDeleteBuffers(1, &buffer.id);
	buffer.id = 0;
	buffer.index = 0;
}
