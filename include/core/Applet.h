#ifndef MUZZLE_CORE_APPLET_H
#define MUZZLE_CORE_APPLET_H

#include "../backend.h"

struct _mz_applet
{
	int width;
	int height;
	char* window_title;
	mz_window window_handle;
};

typedef struct _mz_applet Applet;

#define APPLET_RESIZEABLE 	0x1
#define APPLET_VSYNC		0x2

MZ_API Applet InitializeApplet(int width, int height, const char* window_title, uint32_t flags);
MZ_API void StartApplet(Applet* self);

#endif // MUZZLE_CORE_APPLET_H