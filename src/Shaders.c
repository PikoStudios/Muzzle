#include "modern_pipeline/Shaders.h"

shader_def load_as_shader_definition(const char* vs_filepath, const char* fs_filepath)
{
    FILE *file = fopen(vs_filepath, "r");
    if (!file)
    {
        log_status(STATUS_ERROR, "Could not load vertex file");
        return (shader_def){0};
    }

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* vs_buffer = malloc(sizeof(char) * (size + 1));
    if (!vs_buffer)
    {
        log_status(STATUS_ERROR, "Could not allocate memory for vertex file");
        return (shader_def){0};
    }

    fread(vs_buffer, 1, size, file);
    vs_buffer[size] = 0;
    fclose(file);

    file = fopen(fs_filepath, "r");
    if (!file)
    {
        log_status(STATUS_ERROR, "Could not load fragment file");
        return (shader_def){0};
    }

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* fs_buffer = malloc(sizeof(char) * (size + 1));
    if (!fs_buffer)
    {
        log_status(STATUS_ERROR, "Could not allocate memory for fragment file");
        return (shader_def){0};
    }

    fread(fs_buffer, 1, size, file);
    fs_buffer[size] = 0;
    fclose(file);

    return (shader_def)
    {
        fs_buffer,
        vs_buffer
    };
}

void unload_shader_definition(shader_def* definition)
{
    free(definition->fragment);
    free(definition->vertex);
}

shader create_shader(shader_def* definition)
{
    #ifdef MUZZLE_DANGEROUS_USE_MODERN_GRAPHICS_PIPELINE
        return rlLoadShaderCode(definition->vertex, definition->fragment);
    #else
        log_status(STATUS_ERROR, "Shaders are only supported on the modern renderer");
    #endif
}
void unload_shader(shader shader)
{
    #ifdef MUZZLE_DANGEROUS_USE_MODERN_GRAPHICS_PIPELINE
        rlUnloadShaderProgram(shader);
    #else
        log_status(STATUS_ERROR, "Shaders are only supported on the modern renderer");
    #endif
}

// TODO: Finish this or else
void enable_shader(shader shader)
{
    #ifdef MUZZLE_DANGEROUS_USE_MODERN_GRAPHICS_PIPELINE
        rlUnloadShaderProgram(shader);
    #else
        log_status(STATUS_ERROR, "Shaders are only supported on the modern renderer");
    #endif
}