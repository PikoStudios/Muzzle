#ifndef MUZZLE_CORE_APPLET_H
#define MUZZLE_CORE_APPLET_H

#include "../backend.h"
#include "Shader.h"
#include "Batch.h"

struct _mz_applet
{
	batch default_batch;
	batch* active_batch;
	shader default_vertex;
	shader default_fragment;
	shader_program default_shader_program;
	int width;
	int height;
	char* window_title;
	mz_window window_handle;
};

typedef struct _mz_applet Applet;

#define MZ_APPLET_RESIZABLE 	0x1
#define MZ_APPLET_VSYNC			0x2

MZ_API mz_boolean keep_applet(Applet* self);
MZ_API mz_boolean keep_applet_delta(Applet* self, double* delta);
MZ_API mz_boolean keep_applet_delta_f(Applet* self, float* delta);
MZ_API void OnAppletUpdate(Applet*);

MZ_API Applet InitializeApplet(int width, int height, const char* window_title, uint32_t flags);
MZ_API void StartApplet(Applet* self);

MZ_API void QuitMuzzle(Applet* self);

#endif // MUZZLE_CORE_APPLET_H