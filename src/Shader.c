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
		printf("\t%s\n", message);
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

vertex_attribute_buffer load_vertex_attribute_buffer(shader_program program)
{	
	vertex_attribute_buffer buffer = {0};
	buffer.program = program;
	
	return buffer; 
}

void add_vertex_attribute(vertex_attribute_buffer* buffer, const char* attribute, size_t elements, vertex_attribute_type type, size_t type_size, mz_boolean normalized)
{
	if (buffer->attributes == NULL)
	{
		buffer->attributes_size = 5;
		buffer->attributes = MZ_MALLOC(sizeof(intptr_t) * buffer->attributes_size);
		buffer->index = 0;
		
		if (buffer->attributes == NULL)
		{
			log_status(STATUS_FATAL_ERROR, "Unable to allocate enough memory for vertex attributes");
		}
	}
	
	else
	{
		buffer->attributes_size += 5;
		buffer->attributes = MZ_REALLOC(buffer->attributes, sizeof(intptr_t) * buffer->attributes_size);
		buffer->index++;
		
		if (buffer->attributes == NULL)
		{
			log_status(STATUS_FATAL_ERROR, "Unable to reallocate enough memory for vertex attributes");
		}
	}
	
	int index = buffer->index * 5;
	
	buffer->attributes[index] = glGetAttribLocation(buffer->program, attribute);
	buffer->attributes[index + 1] = elements;
	buffer->attributes[index + 2] = type;
	buffer->attributes[index + 3] = normalized;
	buffer->attributes[index + 4] = buffer->stride;
	buffer->stride += elements * type_size;
	
	/* this is weird, ill explain...
	==================================
	The stride is always the same for each vertex attribute
	So here we calculate the stride by adding the product of
	how many elements there are in this attribute by how big the type is.
	
	However, we can also use this as an offset, if we knew that the stride before this
	new vertex attribute was X, we know the offset of this attribute is X
	*/
}

void enable_vertex_attributes(vertex_attribute_buffer* buffer)
{
	for (int i = 0; i < buffer->index; i++)
	{
		int index = i*5;
		
		glEnableVertexAttribArray(buffer->attributes[index]);
		glVertexAttribPointer(
			buffer->attributes[index],
			buffer->attributes[index + 1],
			buffer->attributes[index + 2],
			buffer->attributes[index + 3],
			buffer->stride,
			(void*)(buffer->attributes[index + 4])
		);
		
		// buffer->attributes[index to index+4] = [
		//	location, elements, type, normalized, offset
		// ]
	}
}

void unload_vertex_attribute_buffer(vertex_attribute_buffer* buffer)
{
	MZ_FREE(buffer->attributes);
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