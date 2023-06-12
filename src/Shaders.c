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
    
    return id;
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
    
    char* buffer = MZ_MALLOC(sizeof(char) * (filesize + 1));
    
    if (buffer == NULL)
    {
        log_status(STATUS_ERROR, "Failed to allocate memory for string buffer, load_shader:45");
        fclose(file);
        return 0;
    }
    
    fread(buffer, 1, filesize, file);
    buffer[filesize] = '\0';
    fclose(file);
    
    shader result = load_shader_from_string(type, buffer);
    MZ_FREE(buffer);
    
    return result;
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

        glDetachShader(id, vertex);
        glDetachShader(id, fragment);
        glDeleteProgram(id);
        return 0;
    }
    
    glDetachShader(id, vertex);
    glDetachShader(id, fragment);
    
    return id;
}

shader_program link_shader_then_delete(shader* vertex, shader* fragment)
{
    GLuint program = link_shader(*vertex, *fragment);
    unload_shader(vertex);
    unload_shader(fragment);
    
    return program;
}

void upload_shader_int(shader_program program, const char* var, int value)
{
    GLuint uniform_location = glGetUniformLocation(program, var);
    glUseProgram(program);
    glUniform1i(uniform_location, value);
    
    #ifdef MUZZLE_VERBOSE
        log_status(STATUS_INFO, "Uploaded integer to shader");
    #endif
}

void upload_shader_float(shader_program program, const char* var, float value)
{
    GLuint uniform_location = glGetUniformLocation(program, var);
    glUseProgram(program);
    glUniform1f(uniform_location, value);
    
    #ifdef MUZZLE_VERBOSE
        log_status(STATUS_INFO, "Uploaded float to shader");
    #endif
}

void upload_shader_vec2(shader_program program, const char* var, vec2 value)
{
    GLuint uniform_location = glGetUniformLocation(program, var);
    glUseProgram(program);
    glUniform2f(uniform_location, value.x, value.y);
    
    #ifdef MUZZLE_VERBOSE
        log_status(STATUS_INFO, "Uploaded vec2 to shader");
    #endif
}

void upload_shader_vec3(shader_program program, const char* var, vec3 value)
{
    GLuint uniform_location = glGetUniformLocation(program, var);
    glUseProgram(program);
    glUniform3f(uniform_location, value.x, value.y, value.z);
    
    #ifdef MUZZLE_VERBOSE
        log_status(STATUS_INFO, "Uploaded vec3 to shader");
    #endif
}

void upload_shader_vec4(shader_program program, const char* var, vec4 value)
{   
    GLuint uniform_location = glGetUniformLocation(program, var);
    glUseProgram(program);
    glUniform4f(uniform_location, value.x, value.y, value.z, value.w);
    
    #ifdef MUZZLE_VERBOSE
        log_status(STATUS_INFO, "Uploaded vec4 to shader");
    #endif
}

void upload_shader_mat3(shader_program program, const char* var, mat3 value)
{
    MZ_ASSERT_NO_MSG(value != NULL)

    GLuint uniform_location = glGetUniformLocation(program, var);
    glUseProgram(program);
    glUniformMatrix3fv(uniform_location, 1, MUZZLE_FALSE, value);
    
    #ifdef MUZZLE_VERBOSE
        log_status(STATUS_INFO, "Uploaded mat3 to shader");
    #endif
}

void upload_shader_mat4(shader_program program, const char* var, mat4 value)
{
    MZ_ASSERT_NO_MSG(value != NULL)

    GLuint uniform_location = glGetUniformLocation(program, var);
    glUseProgram(program);
    glUniformMatrix3fv(uniform_location, 1, MUZZLE_FALSE, value);
    
    #ifdef MUZZLE_VERBOSE
        log_status(STATUS_INFO, "Uploaded mat4 to shader");
    #endif
}

void begin_shader_program(shader_program shader)
{
    glUseProgram(shader);
}

void end_shader_program()
{
    glUseProgram(0);
}

void unload_shader_program(shader_program* shader)
{
    glDeleteProgram(*shader);
    *shader = 0;
}

void unload_shader(shader* shader)
{
    glDeleteShader(*shader);
    *shader = 0;
}