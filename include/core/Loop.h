#pragma once
#include <stdbool.h>
#include "../backend.h"
// Render and Update game here



MZ_API void OnAppletUpdate();

#ifdef __cplusplus
extern "C" MZ_API bool keep_applet(MUZZLE_WINDOW window);
#else
MZ_API bool keep_applet(MUZZLE_WINDOW window);
#endif

