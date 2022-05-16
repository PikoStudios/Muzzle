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
    size = ftell(file);
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
    MZ_FREE(definition->fragment);
    MZ_FREE(definition->vertex);
}

shader create_shader(shader_def* definition)
{
    #ifdef MUZZLE_USE_MODERN_RENDERER
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

        return (shader) { locations, id };
    #else
        log_status(STATUS_ERROR, "Shaders are only supported on the modern renderer");
        return (shader){0};
    #endif
}
void unload_shader(shader* shader)
{
    #ifdef MUZZLE_USE_MODERN_RENDERER
        void* data = __internal_rlgl_get_data_structure();
        if (shader->id != rlGetShaderIdDefault())
        {
            rlUnloadShaderProgram(shader->id);
            MZ_FREE(shader->locations);
        }
    #else
        log_status(STATUS_ERROR, "Shaders are only supported on the modern renderer");
    #endif
}

// TODO: Finish this or else
void enable_shader(shader* shader)
{
    #ifdef MUZZLE_USE_MODERN_RENDERER
        rlSetShader(shader->id, shader->locations);
    #else
        log_status(STATUS_ERROR, "Shaders are only supported on the modern renderer");
    #endif
}