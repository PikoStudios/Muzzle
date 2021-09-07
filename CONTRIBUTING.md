# Contributing to Muzzle
Do you want to contribute to the Muzzle Game Framework? <br /> Please read this guide on the layout of the game framework, its naming scheme, and how it works!

## What to contribute on
***

* `Codebase` - Work on the actual codebase of Muzzle.
* `Docs, Tutorials and/or examples` - Help with writing docs, making tutorials, or examples!
* `Testing` - Help find bugs with Muzzle. For this go to [Testing]()
* `Other` - Of course this list is not the only stuff you can contibute to. These are just suggestions

## Resources
[Naming Scheme]()

## Naming Scheme
***
Muzzle follows PascalCase and snake_case.

**When to follow PascalCase** <br>
PascalCase Should only be followed for Initialization/Exiting functions. For example, the code to show a blank window:
```c
#define MUZZLE_DEPS
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet applet;

void OnAppletUpdate()
{

    while (keep_applet(applet.window_handle))
    {
        begin_drawing();
            clear_screen(GRAY);
        end_drawing(&applet);
    }
    
}

int main(void)
{
    applet = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Blank Window", MUZZLE_FALSE, MUZZLE_FALSE);
    StartApplet(&applet);

    QuitMuzzle(applet);
    return 0;
}
``` 
has `InitializeApplet`, `StartApplet`, `QuitMuzzle`, `Muzzle.h`, `OnAppletUpdate`, and `Applet` as PascalCase. All the code in `OnAppletUpdate` is in snake_case.

This is the naming scheme of Muzzle. All internal functions/headers/source files, functions meant to be run inside OnAppletUpdate, or types are snake_cased. 

<br />All Initialization/Exit/Functions are PascalCase. The only exception to this rule is the `Applet` type. <br />

All non-internal headers and source files should also have the first letter be a captial. Some execptions are `tint.h`, `vector.h` and example  source files

All examples and its files should follow snake_case except `CMakeLists.txt`

**all Macros in Muzzle obviously use UPPER_CASE_SNAKE_CASE**

## Testing
***
If you find a bug, please leave an issue on GitHub. If you have a suggestion. You can leave them on the [Github Discussion](https://github.com/PikoStudios/Muzzle/discussions/16) for suggestions and/or [The Official PikoStudios Discord Server](https://discord.gg/Rw2FdYw5dK)