#include "Muzzle.h"


void QuitMuzzle(Applet applet)
{
    rlglClose();
    glfwDestroyWindow(applet.window_handle);
    glfwTerminate();
}

