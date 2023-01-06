![Muzzle Logo](https://github.com/PikoStudios/Muzzle/blob/main/.github/assests/muzzle.png?raw=true)



[Discord Server](https://discord.gg/Rw2FdYw5dK) | [Twitter](https://twitter.com/piko_studios)

![Discord](https://img.shields.io/discord/784899614410670090?color=%23AAA62C&label=PikoStudios%20Discord%20Server&style=flat-square)
***
Muzzle is an open-source C99 game framework that is easy-to-use and lightweight, but still exposes lower-level APIs.

## Example Window
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
    applet = InitalizeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "My first Muzzle app!", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&applet);

    QuitMuzzle(applet);
    return 0;
}
```

## Getting Started
Muzzle now includes a set-up script that configures Muzzle, but it is still in the testing stage, and is not recommened for use. For now, you can follow these steps to configure Muzzle

To compile all the prerequisites, you will need the *following*:
 - CMake
 - Git
 - A C compiler, such as GCC
 - A build Tool, such as GNU Make

First, fetch the repository with Git. This may take a while, as Git will also need to fetch other repositories such as GLFW
```bash
git clone https://github.com/pikostudios/muzzle --recursive
```

Now navigate yourself to the `{repository}/deps/glfw` folder and check if the submodule installed properly
```bash
cd ./muzzle/deps/glfw
cd deps/glfw
ls # <-- deps/glfw should not be empty if the sumbodules installed properly
```

Create two new folders, `build` and `lib` and navigate into the build folder
```bash
mkdir build, lib
cd build
```

We will now generate the build scripts using CMake. CMake has many generators which you can see in the help command, for this example we will be using `Unix Makefiles`
```bash
cmake .. -G "Unix Makefiles"
```

If everything went well with the generatation, we can run the build scripts
```bash
make
make install
```

Now, you can try to compile one of the examples. Navigate out of the `deps/glfw` folder back to the repository root, then go to `examples/blank_window`
```bash
mkdir build
cd build
cmake .. -G "Unix Makefiles"
make
```

That's it, you just setup Muzzle! Now whenever working on projects, you can copy the CMakeLists.txt in the repository root as a template. 
Reminder, you do not need to delete the `build` folder when you want to recompile. Doing this will only force you to run more commands and regenerate + recompile your entire project + recompiling Muzzle source code too.

## Static Linking
You can compile Muzzle to a static library to reduce inital compile times, but with CMake, your compile times will be shortened after the first compile.

## Licensing
Muzzle is freely usable under the MIT-License, but if you wish to support the project, you can contact us to purchase a license.