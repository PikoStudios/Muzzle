![Muzzle Logo](https://github.com/PikoStudios/Muzzle/blob/main/.github/assests/muzzle.png?raw=true)



[Discord Server](https://discord.gg/Rw2FdYw5dK) | [Twitter](https://twitter.com/piko_studios)

![Discord](https://img.shields.io/discord/784899614410670090?color=%23AAA62C&label=PikoStudios%20Discord%20Server&style=flat-square)
<a href='https://ko-fi.com/E1E6MX8G1' target='_blank'><img height='36' style='border:0px;height:18px;' src='https://storage.ko-fi.com/cdn/kofi1.png?v=6' border='0' alt='Buy Me a Coffee at ko-fi.com' /></a>
***
Muzzle is an open-source C11 game framework that is easy-to-use and lightweight, but still exposes lower-level APIs.

## Example Window
```c
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void applet_loop(mz_applet* applet)
{
    while (mz_keep_applet(applet))
    {
        mz_begin_drawing(applet);
            mz_clear_screen(TINT_GRAY);
        mz_end_drawing(applet);
    }
}

int main(void)
{
    mz_applet applet = mz_initialize_applet("My Muzzle App", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_RESIZBALE | APPLET_FLAG_VSYNC | APPLET_FLAG_TRACK_DELTA_TIME);
    mz_start_applet(&applet, applet_loop);

    mz_terminate_applet(&applet);
    return 0;
}
```

## Getting Started
Muzzle requires two dependencies to be built:
 - GLFW (deps/glfw)
 - Freetype (deps/freetype)


Both of these dependencies can be built with CMake, simply run the following to build all dependencies:
```bash
cd deps/glfw
mkdir build
mkdir lib
cd build
cmake ..
make
cd src
cp libglfw3.a ../../lib/libglfw3.a
cd ../../..
cd deps/freetype
mkdir build
mkdir lib
cd build
cmake ..
make
cp libfreetype.a ../lib/libfreetype.a
cd ../..
```

After building all the dependencies, navigate to the `template` directory. Here you will find a simple project setup. Copy this directory and edit `MUZZLE_ROOT` in the `CMakeLists.txt` to where your installation of Muzzle will be. Next generate the project with cmake and build!

## Contributing
View [main/CONTRIBUTING.md](https://github.com/PikoStudios/Muzzle/blob/main/CONTRIBUTING.md) if on `main` branch, else, visit `CONTRIBUTING.MD` file in the respective branch

## Licensing
Muzzle is freely usable under the MIT-License, but if you wish to support the project, you can contact us to purchase a license.
