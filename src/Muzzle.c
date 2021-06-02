#include "Muzzle.h"


void QuitMuzzle(Applet applet)
{
    log_status(INFO, "Closing Window");
    glfwDestroyWindow(applet.window_handle);
    log_status(INFO, "Terminating OpenGL Context");
    glfwTerminate();
}

