#include "modern_pipeline/Shaders.h"

shader load_shader(shader_type type, const char* filepath)
{
    // Read file
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

    GLuint id = glCreateShader(type);
    if (id == 0)
    {
        log_status(STATUS_ERROR, "Could not create shader");
        return id;
    }

    int status = 0;

    glShaderSource(id, 1, (const char**)(&buffer), NULL);
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);

    if (status == MUZZLE_FALSE)
    {
        log_status(STATUS_ERROR, "Shader failed to compile, More info:");

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char infolog[length + 1];
        glGetShaderInfoLog(shader, length, NULL, infolog);

        printf("\t%s\n", infolog);
    }
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
        return;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return id;
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