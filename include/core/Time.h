#pragma once
#include "../backend.h"

void update_delta_time();

double get_delta_time();
float get_delta_time_float();

struct __time_spec
{ 
    __int64     tv_sec;
    __int32     tv_nsec;
};

