#pragma once
#include "Muzzle.h"


typedef struct Cube
{
    Vector2 position;
    float width, height;
    float length;
    Color tint;

} Cube;

// Render a cube
// alernative to RenderCube
void mz_DrawCube(Cube Cube);
// Render a cube
// alernative to mz_DrawCube
void RenderCube(Cube Cube);