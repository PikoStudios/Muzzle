// #define MUUZZLE_RAYLIB <--- to use the raylib backend. For this example we are just going to be using the RLGL backend
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TARGET_FPS 60 // You can set this to 0 if you dont want a fps lock

void OnAppletUpdate()
{
    tint my_color = {184, 213, 238, 255};

    while (IsAppletAlive())
    {
        begin_drawing();
         clear_screen(my_color); // currently does not work :(
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
