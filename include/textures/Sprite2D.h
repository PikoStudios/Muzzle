#pragma once
#include "raylib.h"


typedef struct Sprite2D
{
    Texture2D texture;
    Vector2 position;
    Color tint;
} Sprite2D;

void DrawSprite2D(Sprite2D sprite);