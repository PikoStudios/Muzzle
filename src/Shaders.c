#include "modern_pipeline/Shaders.h"


shader_context create_shader_context()
{
    return glCreateProgram();
}

void link_shader(shader_context context, shader shader)
{
    glAttachShader(context, shader);
}

void link_shader_context(shader_context context)
{
    glLinkProgram(context);
}

void use_shaders(shader_context context)
{
    glUseProgram(context);
}

shader create_default_vertex_shader()
{
    return create_shader(VERTEX_SHADER, &__internal_muzzle_defaults_shader_vertex_shader_source);
}

shader create_default_fragment_shader(tint color_drawn)
{
    const char source[FRAGMENT_SHADER_SOURCE_SIZE];
    sprintf(source, "#version 330 core\n""out vec4 FragColor;\n""\n""void main()\n""{\n"
    "FragColor = vec4(%.1ff, %.1ff, %.1ff, %.1ff);\n""}\n", color_drawn.r / 255, color_drawn.g / 255, color_drawn.b / 255, color_drawn.a / 255);

    return create_shader(FRAGMENT_SHADER, &source);
}

shader create_shader(shader_type type, const char* source)
{
    shader buf;
    buf = glCreateShader(type);

    glShaderSource(buf, 1, &source, NULL);
    glCompileShader(buf);

#ifndef MZ_DONT_GET_SHADER_RESULT

    int result;
    char log[SHADER_RESULT_LOG_SIZE];

    glGetShaderiv(buf, GL_COMPILE_STATUS, &result);

    if (!result)
    {
        glGetShaderInfoLog(buf, SHADER_RESULT_LOG_SIZE, NULL, log);
	
	char output[SHADER_RESULT_BUFFER_SIZE];
	sprintf(output, "Failed to create shader\nReason: %s", output);
        
	log_status(STATUS_ERROR, output);
    }

#endif

    return buf;
}

void unload_shader(shader shader)
{
    glDeleteShader(shader);
}
