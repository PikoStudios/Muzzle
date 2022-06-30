#pragma once

#ifdef MUZZLE_DEPS
    #define CUTE_SOUND_SCALAR_MODE
    #define CUTE_SOUND_IMPLEMENTATION
#endif

#include "../deps/cute_sound/cute_sound.h"
#include "../backend.h"
#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
#elif __linux__
    #ifndef MUZZLE_FORCE_WAYLAND
        #define GLFW_EXPOSE_NATIVE_X11
    #else
        #define GLFW_EXPOSE_NATIVE_WAYLAND
    #endif
#elif __APPLE__
    #define GLFW_EXPOSE_NATIVE_COCOA
#endif


#include "../deps/glfw/include/GLFW/glfw3native.h"

#include <stdio.h>
#include "Applet.h"

#define DEFAULT_PLAY_FREQUENCY_HZ 44100
#define DEFAULT_BUFFERED_SAMPLES 15
#define DEFAULT_PLAYING_POOL 5

#ifdef MUZZLE_AUDIO_FORCE_SDL2
    #define CUTE_SOUND_FORCE_SDL
#endif

typedef cs_context_t audio_context;
typedef struct audio
{
    cs_loaded_sound_t loaded;
    cs_playing_sound_t sound;    
} audio;

#ifdef __cplusplus
extern "C" {
#endif

MZ_API audio_context* initialize_audio_context(Applet *applet, unsigned play_freq_hz, int buffered_samples, int playing_pool_count);


MZ_API audio load_audio_wav(const char* filepath);
MZ_API void play_audio(audio_context* ctx, audio* sound);

MZ_API void mix_audio_context(audio_context* ctx);
MZ_API void spawn_mix_thread(audio_context* ctx);

MZ_API void unload_audio(audio* sound);
MZ_API void unload_audio_context(audio_context* ctx);

// TODO: Look into cs_sleep(); and implement it in Muzzle.h

#ifdef __cplusplus
}
#endif
