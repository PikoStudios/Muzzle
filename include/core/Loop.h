#pragma once
#include <stdbool.h>
#include "../backend.h"
// Render and Update game here

#ifdef _cplusplus
    extern "C" {
#endif

void OnAppletUpdate();
bool keep_applet(MUZZLE_WINDOW window);

#ifdef _cplusplus
}
#endif
