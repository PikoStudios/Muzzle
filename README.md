![Muzzle Logo](https://github.com/PikoStudios/Muzzle/blob/main/.github/assests/muzzle.png?raw=true)



[Discord Server](https://discord.gg/Rw2FdYw5dK) | [Twitter](https://twitter.com/piko_studios)

![Discord](https://img.shields.io/discord/784899614410670090?color=%23AAA62C&label=PikoStudios%20Discord%20Server&style=flat-square)
***
Muzzle is a Open-Source C99 Game Framework

## Example:
```c
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet blank_window;

void OnAppletUpdate()
{
    while (keep_applet(blank_window.window_handle))
    {
        begin_drawing();
            clear_screen(GRAY);
        end_drawing(&blank_window);
    }
    
}

int main(void)
{
    blank_window = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Blank Window", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&blank_window);

    QuitMuzzle(blank_window);
    return 0;
}

```
 
## Features
* Creating a Window
* Clearing the Screen
* Drawing Rectangle
* Keyboard Input
* Mouse Input
* Sprite Rendering
* Drawing Circle
* Loop
* Text Rendering
* Font Loading


## How to build
There is a CMakeLists.txt avaliable (It May not work on linux)

If you do not want to use CMake
Here is how it can be done with gcc

Linux:
```
$ gcc main.c -I[Muzzle Install path] -L[Path to folder with GLFW3 Lib Files] -lGl -lglfw -lm
```

Windows + MinGW:
```
$ gcc main.c -I[Muzzle Install path] -L[Path to folder with GLFW3 Lib Files] -lglfw3 -lopengl32 -lgdi32 -o main.exe
```
