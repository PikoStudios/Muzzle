#include "core/Loop.h"

bool IsAppletAlive(MUZZLE_WINDOW window)
{
    return !glfwWindowShouldClose(window);
}