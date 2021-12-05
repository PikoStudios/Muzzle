#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Error.h"

// Debugger meant for the developer, log_status() is always an option, but it is more meant for internal use.

enum DEBUG_TYPES
{
    NATURAL_DEBUG,
    WARN_DEBUG,
    ERROR_DEBUG,
    HALT_DEBUG,
};

typedef struct debugger
{
    int debug_type;
    FILE* log;
    FILE* out;
    FILE* err;

    const char* debugger_name;
} debugger;

void trigger_debugger(const char* msg, debugger* self, int debug_type);