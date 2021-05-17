// #define MUUZZLE_RAYLIB <--- to use the raylib backend. For this example we are just going to be using the RLGL backend
#include "../../../include/Muzzle.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TARGET_FPS 60 // You can set this to 0 if you dont want a fps lock

void OnAppletUpdate()
{
    tint white = {255,255,255,255};

    while (IsAppletAlive())
    {
        begin_drawing(white);
        end_drawing();
    }
    
}

int main(void)
{
    Applet blank_window = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, TARGET_FPS, "Muzzle [core] - Blank Window");
    StartApplet(&blank_window);

    QuitMuzzle();
    return 0;
}
