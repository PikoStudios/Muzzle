#include "Muzzle.h"

void OnAppletUpdate()
{
    while(IsAppletAlive())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
        EndDrawing();
    }
}


int main(void)
{
    Applet applet = InitalizeApplet(800, 800, 60, "Hello World");
    StartApplet(&applet);

    QuitMuzzle();
    return 0;
}
