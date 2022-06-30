#pragma once
#include "../backend.h"

#ifdef __cplusplus
extern "C" {
#endif


MZ_API void update_delta_time();

MZ_API double get_delta_time();
MZ_API float get_delta_time_float();

#ifdef __cplusplus
}
#endif
