#include "core/Loop.h"

bool keep_applet(MUZZLE_WINDOW window)
{
    return !glfwWindowShouldClose(window);
}