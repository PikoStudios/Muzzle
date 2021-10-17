#include "core/Time.h"

void update_delta_time()
{
    glfwSetTime(0);
}

double get_delta_time()
{
    return glfwGetTime();
}

float get_delta_time_float()
{
    return (float)(glfwGetTime());
}