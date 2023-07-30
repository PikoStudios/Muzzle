#ifndef MUZZLE_MUZZLE_H
#define MUZZLE_MUZZLE_H

#include "backend.h"

#ifndef MUZZLE_EXCLUDE_CORE
#include "core/Applet.h"
#include "core/Error.h"
#include "core/Batch.h"
#include "core/tint.h"
#include "core/Shader.h"
#include "core/vector.h"
#include "core/Drawing.h"
#endif

#ifdef MUZZLE_EXCLUDE_CORE
#warning "Excluding core will break Muzzle if proper subsitutes are not in place"
#endif

#ifdef MUZZLE_INCLUDE_CALLBACK_HOOK_API
#include "core/CallbackHook.h"
#endif

#endif // MUZZLE_MUZZLE_H