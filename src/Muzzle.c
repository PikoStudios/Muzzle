#include "Muzzle.h"


void QuitMuzzle(Applet applet)
{
    #ifdef MUZZLE_DANGEROUS_USE_MODERN_GRAPHICS_PIPELINE
        log_status(STATUS_INFO, "Closing Modern Renderer Context");
        rlglClose();
    #endif

    log_status(STATUS_INFO, "Closing Window");
    glfwDestroyWindow(applet.window_handle);
    log_status(STATUS_INFO, "Terminating OpenGL Context");
    glfwTerminate();
}