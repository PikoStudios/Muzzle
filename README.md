![Muzzle Logo](https://github.com/PikoStudios/Muzzle/blob/main/.github/assests/muzzle.png?raw=true)

**This is a W.I.P Branch and may not be stable**

### Redesigned Parts:
 - rectangle
 - drawing.h
 - backend.h


[Discord Server](https://discord.gg/Rw2FdYw5dK) | [Twitter](https://twitter.com/piko_studios)
***
Muzzle is a Open-Source C99 Game Framework with support for many graphics backends such as
 - Raylib
 - RLGL + Raylib (OpenGL Legacy like wrapper for Modern OpenGL)
 - SDL2 (TODO)

## Example:
```c
#include <Muzzle.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TARGET_FPS 60

void OnAppletUpdate()
{
    while (IsAppletAlive())
    {
        begin_drawing(COLOR_WHITE);
        end_drawing();
    }
}

int main(void)
{
    Applet myApplet = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, TARGET_FPS, "Muzzle - Window");
    StartApplet(&myApplet);

    QuitMuzzle();
    return 0;
}
```
 
## Features
***Please wait for more details soon on this topic***

## How to contribute
Want to contribute, Well just fork the repo, make changes, and make a pull request

***Please wait for more details soon on this topic***

## How to build
***Please wait for more details soon on this topic***
