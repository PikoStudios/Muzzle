#include "modern_pipeline/Shaders.h"

shader load_shader_from_string(shader_type type, const char* shader_code)
{
    GLuint id = glCreateShader(type);
    if (id == 0)
    {
        log_status(STATUS_ERROR, "Could not create shader");
        return id;
    }

    int status = 0;

    glShaderSource(id, 1, (const char**)(&shader_code), NULL);
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);

    if (status == MUZZLE_FALSE)
    {
        log_status(STATUS_ERROR, "Shader failed to compile, More info:");

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char infolog[length + 1];
        glGetShaderInfoLog(id, length, NULL, infolog);

        printf("\t%s\n", infolog);
    }
}

shader load_shader(shader_type type, const char* filepath)
{
    FILE* file = fopen(filepath, "r");
    if (!file)
    {
        log_status(STATUS_ERROR, "Could not read shader file");
        return 0;
    }
    
    fseek(file, 0, SEEK_END);
    const int filesize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char buffer[filesize + 1];
    
    fread(buffer, 1, filesize, file);
    buffer[filesize] = '\0';
    fclose(file);
    
    return load_shader_from_string(type, buffer);
}

shader_program link_shader(shader vertex, shader fragment)
{
    GLuint id = glCreateProgram();
    
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    int status = 0;
    glGetProgramiv(id, GL_LINK_STATUS, &status);

    if (status == MUZZLE_FALSE)
    {
        log_status(STATUS_ERROR, "Shader Program failed to link, More info:");

        int length;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

        char infolog[length + 1];
        glGetProgramInfoLog(id, length, NULL, infolog);

        printf("\t%s\n", infolog);

        glDeleteProgram(id);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return 0;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return id;
}

void upload_shader_int(shader_program program, const char* var, int value)
{
    int uniform_location = glGetUniformLocation(program, var);
    glUseProgram(program);
    glUniform1i(uniform_location, value);
    
    #ifdef MUZZLE_VERBOSE
        log_status(STATUS_INFO, "Uploaded integer to shader");
    #endif
}

void upload_shader_float(shader_program program, const char* var, float value)
{
    int uniform_location = glGetUniformLocation(program, var);
    glUseProgram(program);
    glUniform1f(uniform_location, value);
    
    #ifdef MUZZLE_VERBOSE
        log_status(STATUS_INFO, "Uploaded float to shader");
    #endif
}

void upload_shader_vec2(shader_program program, const char* var, vec2 value)
{
    int uniform_location = glGetUniformLocation(program, var);
    glUseProgram(program);
    glUniform2f(uniform_location, value.x, value.y);
    
    #ifdef MUZZLE_VERBOSE
        log_status(STATUS_INFO, "Uploaded vec2 to shader");
    #endif
}

void upload_shader_vec3(shader_program program, const char* var, vec3 value)
{
    int uniform_location = glGetUniformLocation(program, var);
    glUseProgram(program);
    glUniform3f(uniform_location, value.x, value.y, value.z);
    
    #ifdef MUZZLE_VERBOSE
        log_status(STATUS_INFO, "Uploaded vec3 to shader");
    #endif
}

void upload_shader_vec4(shader_program program, const char* var, vec4 value)
{
    int uniform_location = glGetUniformLocation(program, var);
    glUseProgram(program);
    glUniform4f(uniform_location, value.x, value.y, value.z, value.w);
    
    #ifdef MUZZLE_VERBOSE
        log_status(STATUS_INFO, "Uploaded vec4 to shader");
    #endif
}

void attach_shader_program(shader_program shader)
{
    glUseProgram(shader);
}

void unload_shader_program(shader_program shader)
{
    glDeleteProgram(shader);
}

void detach_shader_program()
{
    glUseProgram(0);
}