#define MUZZLE_SUPPORT_SPRITES
//#define MUZZLE_VERBOSE
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet sprite_rendering;

void OnAppletUpdate()
{
    tint my_color = {84, 84, 84, 255};
    sprite spr = load_sprite("../muzzle.png"); // Upload sprite into GPU
    // If using CMake, add ../ because the exe is in the build folder
    
    
    while (keep_applet(sprite_rendering.window_handle))
    {
        begin_drawing();
            clear_screen(my_color);

            draw_sprite(&spr, 10,10, 1.0f, 0.0f, WHITE);
        end_drawing(&sprite_rendering);
    }
    
    unload_sprite(&spr); //Unload Sprite from GPU
}

int main(void)
{
    sprite_rendering = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Sprite Rendering", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&sprite_rendering);

    QuitMuzzle(sprite_rendering);
    return 0;
}
