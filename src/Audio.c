#include "core/Audio.h"

audio_context* initialize_audio_context(Applet *applet, unsigned play_freq_hz, int buffered_samples, int playing_pool_count)
{
#ifdef _WIN32
    void* win = glfwGetWin32Window(applet->window_handle);
#elif __linux__
    #ifndef MUZZLE_FORCE_WAYLAND
        void* win = glfwGetX11Window(applet->window_handle);
    #else
        void* win = glfwGetWaylandWindow(applet->window_handle);
    #endif
#elif __APPLE__
    void* win = glfwGetCocoaWindow(applet->window_handle);
#endif
    cs_context_t* buffer = cs_make_context(win, play_freq_hz, buffered_samples, playing_pool_count, NULL);
    

    return buffer;
}


audio load_audio_wav(const char* filepath)
{
    cs_loaded_sound_t loaded_buffer = {0};
    cs_playing_sound_t playing_sound_buffer = {0};

    
    loaded_buffer = cs_load_wav(filepath);
    if (cs_error_reason != NULL) printf("Low level fatal error, refer to the following string for error details: %s)\n", cs_error_reason);
    else playing_sound_buffer = cs_make_playing_sound(&loaded_buffer);

    return (audio)
    {
        loaded_buffer,
        playing_sound_buffer
    };
}

void play_audio(audio_context* ctx, audio* sound)
{
    if (cs_insert_sound(ctx, &sound->sound) == 0) log_status(STATUS_ERROR, "Unable to insert audio into context (aka, unable to play audio)");
}

void unload_audio(audio* sound)
{
    cs_free_sound(&sound->loaded);
}

void unload_audio_context(audio_context* ctx)
{
    cs_shutdown_context(ctx);
}

void mix_audio_context(audio_context* ctx)
{
    cs_mix(ctx);
}

void spawn_mix_thread(audio_context* ctx)
{
    cs_spawn_mix_thread(ctx);
}