#include "Muzzle.h"


void QuitMuzzle(MUZZLE_WINDOW window)
{
    rlglClose();
    glfwDestroyWindow(window);
    glfwTerminate();
}

