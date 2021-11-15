#include "Muzzle.h"


void QuitMuzzle(Applet applet)
{
    log_status(STATUS_INFO, "Closing Window");
    glfwDestroyWindow(applet.window_handle);
    log_status(STATUS_INFO, "Terminating OpenGL Context");
    glfwTerminate();
}

void create_shared_variable(void* variable, int index)
{
    __muzzle_shared_variable_array[index] = variable;
}

void remove_shared_variable(int index)
{
    __muzzle_shared_variable_array[index] = NULL;
}

void* get_shared_variable(int index)
{
    return __muzzle_shared_variable_array[index];
}