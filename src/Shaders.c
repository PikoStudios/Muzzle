#include "modern_pipeline/Shaders.h"

shader_def load_as_shader_definition(const char* vs_filepath, const char* fs_filepath)
{
    // Load vertex shader
    FILE *file = fopen(vs_filepath, "r");
    if (!file)
    {
        log_status(STATUS_ERROR, "Could not load vertex file");
        return (shader_def){0};
    }

    fseek(file, 0, SEEK_END);
    const int filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* vs_buffer[filesize + 1];

    fread(vs_buffer, 1, size, file);
    vs_buffer[filesize] = '\0';
    fclose(file);

    // Load fragment shader
    file = fopen(fs_filepath, "r");
    if (!file)
    {
        log_status(STATUS_ERROR, "Could not load fragment file");
        return (shader_def){0};
    }

    fseek(file, 0, SEEK_END);
    filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* fs_buffer[filesize + 1];

    fread(fs_buffer, 1, size, file);
    fs_buffer[filesize] = '\0';
    fclose(file);

    return (shader_def)
    {
        fs_buffer,
        vs_buffer
    };
}

shader create_shader(shader_def* definition)
{
    unsigned int id = rlLoadShaderCode(definition->vertex, definition->fragment);
    int *locations = MZ_CALLOC(RL_MAX_SHADER_LOCATIONS, sizeof(int));

    if (locations == NULL)
    {
        log_status(STATUS_FATAL_ERROR, "Failed to allocate memory for shader");
    }

    for (int i = 0; i < RL_MAX_SHADER_LOCATIONS; i++) locations[i] = -1;
    if (id > 0)
    {
        locations[RL_SHADER_LOC_VERTEX_COLOR] =         rlGetLocationAttrib(id, MZ_SHADER_ATTRIB_NAME_POSITION);
        locations[RL_SHADER_LOC_VERTEX_TEXCOORD01] =    rlGetLocationAttrib(id, MZ_SHADER_ATTRIB_NAME_TEXCOORD);
        locations[RL_SHADER_LOC_VERTEX_TEXCOORD02] =    rlGetLocationAttrib(id, MZ_SHADER_ATTRIB_NAME_TEXCOORD2);
        locations[RL_SHADER_LOC_VERTEX_NORMAL] =        rlGetLocationAttrib(id, MZ_SHADER_ATTRIB_NAME_NORMAL);
        locations[RL_SHADER_LOC_VERTEX_TANGENT] =       rlGetLocationAttrib(id, MZ_SHADER_ATTRIB_NAME_TANGENT);
        locations[RL_SHADER_LOC_VERTEX_COLOR] =         rlGetLocationAttrib(id, MZ_SHADER_ATTRIB_NAME_COLOR);

        locations[RL_SHADER_LOC_MATRIX_MVP] =           rlGetLocationUniform(id, MZ_SHADER_UNIFORM_NAME_MVP);
        locations[RL_SHADER_LOC_MATRIX_VIEW] =          rlGetLocationUniform(id, MZ_SHADER_UNIFORM_NAME_VIEW);
        locations[RL_SHADER_LOC_MATRIX_PROJECTION] =    rlGetLocationUniform(id, MZ_SHADER_UNIFORM_NAME_PROJECTION);
        locations[RL_SHADER_LOC_MATRIX_MODEL] =         rlGetLocationUniform(id, MZ_SHADER_UNIFORM_NAME_MODEL);
        locations[RL_SHADER_LOC_MATRIX_NORMAL] =        rlGetLocationUniform(id, MZ_SHADER_UNIFORM_NAME_NORMAL);

        locations[RL_SHADER_LOC_COLOR_DIFFUSE] =        rlGetLocationUniform(id, MZ_SHADER_UNIFORM_NAME_COLOR);
        locations[RL_SHADER_LOC_MAP_DIFFUSE] =          rlGetLocationUniform(id, MZ_SHADER_SAMPLER2D_NAME_TEXTURE0);  // SHADER_LOC_MAP_ALBEDO
        locations[RL_SHADER_LOC_MAP_SPECULAR] =         rlGetLocationUniform(id, MZ_SHADER_SAMPLER2D_NAME_TEXTURE1); // SHADER_LOC_MAP_METALNESS
        locations[RL_SHADER_LOC_MAP_NORMAL] =           rlGetLocationUniform(id, MZ_SHADER_SAMPLER2D_NAME_TEXTURE2);
    }

    log_status(STATUS_INFO, "Shader initalized");
    return (shader) { locations, id };
}
void unload_shader(shader* shader)
{
    if (shader->id != rlGetShaderIdDefault())
    {
        rlUnloadShaderProgram(shader->id);
        MZ_FREE(shader->locations);
    }

    log_status(STATUS_SUCCESS, "Unloaded shader");
}

// TODO: Finish this or else
void enable_shader(shader* shader)
{
    
    rlSetShader(shader->id, shader->locations);
    log_status(STATUS_INFO, "Enabled shader");
}