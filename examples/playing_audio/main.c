#define MUZZLE_DEPS
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet applet;

void OnAppletUpdate()
{
    #ifdef _WIN32
        audio_context* ctx = initialize_audio_context(&applet, DEFAULT_PLAY_FREQUENCY_HZ, DEFAULT_BUFFERED_SAMPLES, DEFAULT_PLAYING_POOL);
    #else
        audio_context* ctx = initialize_audio_context(DEFAULT_PLAY_FREQUENCY_HZ, DEFAULT_BUFFERED_SAMPLES, DEFAULT_PLAYING_POOL);
    #endif

    audio sound = load_audio_wav("../audio.wav");
    spawn_mix_thread(ctx);
    

    while (keep_applet(applet.window_handle))
    {
        begin_drawing();
            clear_screen(GRAY);
        end_drawing(&applet);

        play_audio(ctx, &sound);
        unload_audio(&sound);
    }
    
}

int main(void)
{
    applet = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Playing Audio", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&applet);

    QuitMuzzle(applet);
    return 0;
}
