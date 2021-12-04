#pragma once
#include <stdbool.h>
#include "../backend.h"
// Render and Update game here



void OnAppletUpdate();

#ifdef __cplusplus
extern "C" bool keep_applet(MUZZLE_WINDOW window);
#else
bool keep_applet(MUZZLE_WINDOW window);
#endif

