#include "core/Loop.h"

bool IsAppletAlive()
{
    return !WindowShouldClose();
}