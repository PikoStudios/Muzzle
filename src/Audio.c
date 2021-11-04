#include "core/Audio.h"

audio_context* initialize_audio_context(unsigned play_freq_hz, int buffered_samples, int playing_pool_count)
{
    cs_context_t* buffer = cs_make_context(NULL, play_freq_hz, buffered_samples, playing_pool_count, NULL);
    cs_spawn_mix_thread(buffer);

    return buffer;
}

audio load_audio_wav(const char* filepath)
{
    cs_loaded_sound_t loaded_buffer = cs_load_wav(filepath);
    cs_playing_sound_t playing_sound_buffer = cs_make_playing_sound(&loaded_buffer);

    return (audio)
    {
        loaded_buffer,
        playing_sound_buffer
    };
}

void play_audio(audio_context* ctx, audio* sound)
{
    cs_insert_sound(ctx, &sound->sound);
}

void unload_audio(audio* sound)
{
    cs_free_sound(&sound->loaded);
}