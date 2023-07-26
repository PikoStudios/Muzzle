#include "core/Shader.h"

shader load_shader_from_string(const char* code, shader_type type)
{
	GLuint id = glCreateShader(type);
	
	if (id == 0)
	{
		log_status(STATUS_ERROR, "Could not create shader");
		return 0;
	}
	
	GLint status = 0;
	glShaderSource(id, 1, (const char**)(&code), NULL);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	
	if (status != GL_TRUE)
	{
		GLsizei log_length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);
		
		GLchar message[log_length];
		glGetShaderInfoLog(id, log_length, NULL, message);
		
		log_status(STATUS_ERROR, "Shader failed to compile, More info:");
		printf("\t%s\n\t%s\n", (type == SHADER_FRAGMENT) ? "Fragment Error" : "Vertex Error", message);
	}
	
	return id;
}

shader load_shader(const char* filename, shader_type type)
{
	FILE* file = fopen(filename, "r");
	
	if (file == NULL)
	{
		log_status(STATUS_ERROR, "Could not read shader file");
		return 0;
	}
	
	fseek(file, 0, SEEK_END);
	const long int size = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	char* buffer = MZ_MALLOC(sizeof(char) * (size+1));
	
	if (buffer == NULL)
	{
		log_status(STATUS_ERROR, "Could not allocate memory for shader string buffer");
		fclose(file);
		return 0;
	}
	
	fread(buffer, size, 1, file);
	buffer[size] = '\0';
	fclose(file);
	
	GLuint id = load_shader_from_string(buffer, type);
	MZ_FREE(buffer);
	
	return id;
}

shader_program link_shader(shader vertex, shader fragment)
{
	GLuint id = glCreateProgram();
	GLint status = 0;
	
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &status);
	
	if (status != GL_TRUE)
	{
		GLsizei log_length = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_length);
		
		GLchar message[log_length];
		glGetProgramInfoLog(id, log_length, NULL, message);
		
		log_status(STATUS_ERROR, "Shader Program failed to link, more info:");
		printf("\t%s\n", message);
	}
	
	glDetachShader(id, vertex);
	glDetachShader(id, fragment);
	
	return id;
}

shader_program link_shader_then_delete(shader* vertex, shader* fragment)
{
	GLuint id = link_shader(*vertex, *fragment);
	unload_shader(vertex);
	unload_shader(fragment);
	
	return id;
}

void upload_uniform_int(shader_program program, const char* uniform, int value)
{
	GLuint loc = glGetUniformLocation(program, uniform);
	glUseProgram(program);
	glUniform1i(loc, value);
}

void upload_uniform_float(shader_program program, const char* uniform, float value)
{
	GLuint loc = glGetUniformLocation(program, uniform);
	glUseProgram(program);
	glUniform1f(loc, value);
}

void upload_uniform_vec2(shader_program program, const char* uniform, vec2 value)
{
	GLuint loc = glGetUniformLocation(program, uniform);
	glUseProgram(program);
	glUniform2f(loc, value.x, value.y);
}

void upload_uniform_vec3(shader_program program, const char* uniform, vec3 value)
{
	GLuint loc = glGetUniformLocation(program, uniform);
	glUseProgram(program);
	glUniform3f(loc, value.x, value.y, value.z);
}

void upload_uniform_vec4(shader_program program, const char* uniform, vec4 value)
{
	GLuint loc = glGetUniformLocation(program, uniform);
	glUseProgram(program);
	glUniform4f(loc, value.x, value.y, value.z, value.w);
}

void unload_shader(shader* shader)
{
	glDeleteShader(*shader);
	*shader = 0;
}

void unload_shader_program(shader_program* program)
{
	glDeleteProgram(*program);
	*program = 0;
}

void unload_shaders(shader** shaders, size_t length)
{
	for (int i = 0; i < length; i++)
	{
		glDeleteShader(*shaders[i]);
		*shaders[i] = 0;
	}
}

void unload_shader_programs(shader_program** programs, size_t length)
{
	for (int i = 0; i < length; i++)
	{
		glDeleteProgram(*programs[i]);
		*programs[i] = 0;
	}
}