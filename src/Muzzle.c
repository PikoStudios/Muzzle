#include "Muzzle.h"


void QuitMuzzle(Applet applet)
{
    log_status(STATUS_INFO, "Closing Window");
    glfwDestroyWindow(applet.window_handle);
    log_status(STATUS_INFO, "Terminating OpenGL Context");
    glfwTerminate();
}