#pragma once
#include "raylib.h"


// 2.5D Sprite
typedef struct Sprite3D
{
    Texture2D texture;
    Vector3 position;
    Color tint;
    float size;
} Sprite3D;

void DrawSprite3D(Sprite3D sprite, Camera camera);