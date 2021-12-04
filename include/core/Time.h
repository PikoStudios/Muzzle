#pragma once
#include "../backend.h"

#ifdef __cplusplus
extern "C" {
#endif


void update_delta_time();

double get_delta_time();
float get_delta_time_float();

struct __time_spec
{ 
    __int64     tv_sec;
    __int32     tv_nsec;
};

#ifdef __cplusplus
}
#endif
