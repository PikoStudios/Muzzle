![Muzzle Logo](https://github.com/PikoStudios/Muzzle/blob/main/.github/assests/muzzle.png?raw=true)



[Discord Server](https://discord.gg/Rw2FdYw5dK) | [Twitter](https://twitter.com/piko_studios)
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
    tint my_color = {35, 35, 142, 1};

    while (!glfwWindowShouldClose(blank_window.window_handle))
    {
        begin_drawing();
            clear_screen(my_color); 
        end_drawing(&blank_window);
    }
    
}

int main(void)
{
    blank_window = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Blank Window", MUZZLE_FALSE, MUZZLE_FALSE);
    StartApplet(&blank_window);

    QuitMuzzle(blank_window);
    return 0;
}

```
 
## Features
* Creating a Window
* Clearing the Screen
* Drawing Rectangle
** dont worry thats not all, im just a little lazy to type them all**


## How to build
A CMake file to build with will be avaliable soon
