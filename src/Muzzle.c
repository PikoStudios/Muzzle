#include "Muzzle.h"


void QuitMuzzle(Applet applet)
{
    glfwDestroyWindow(applet.window_handle);
    glfwTerminate();
}

