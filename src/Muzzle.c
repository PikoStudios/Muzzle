#include "Muzzle.h"


void QuitMuzzle(Applet applet)
{
    log_status(STATUS_INFO, "Closing Window");
    glfwDestroyWindow(applet.window_handle);
    log_status(STATUS_INFO, "Terminating OpenGL Context");
    glfwTerminate();
}

void mz_sleep(int ms)
{
    #ifdef _WIN32
        Sleep(ms);
    #elif __unix__ || __APPLE__
        struct __time_spec x = (struct __time_spec x) { 0, ms * 1000000};
        nanosleep(&x, NULL);
    #endif
}