#ifndef MUZZLE_CORE_CALLBACK_HOOK_H
#define MUZZLE_CORE_CALLBACK_HOOK_H

#define MUZZLE_CALLBACK_HOOK_KEY_INPUT 	0x1
#define MUZZLE_CALLBACK_HOOK_ERROR     	0x2
#define MUZZLE_CALLBACK_HOOK_REISZE	    0x4

#include "..\backend.h"
#include "Applet.h"

// void key_input_callback(Applet* applet, int key, int scancode, int action, int mods);
typedef void (*MZcallback_keyinputfun)(Applet*, int, int, int, int);

// void error_callback(int error_code, const char* description);
typedef void (*MZcallback_errorfun)(int, const char*);

// void resize_callback(Applet* applet, int width, int height);
typedef void (*MZcallback_resizefun)(Applet*, int, int);

union callback_hook_union
{
    MZcallback_keyinputfun key_input_fptr;
    MZcallback_errorfun error_fptr;
    MZcallback_resizefun resize_fptr;
};

MZ_API void muzzle_register_callback(uint8_t target, union callback_hook_union callback);

#endif // MUZZLE_CORE_CALLBACK_HOOK_H