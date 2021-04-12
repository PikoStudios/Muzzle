#pragma once
#include "raylib.h"

typedef struct Circle
{
    int CenterX, CenterY;
    float radius;
    Color tint;
} Circle;

typedef struct Sphere
{
    Vector3 center;
    float radius;
    Vector3 RotationAxis;
    float RotationAngle;
    Color tint;
} Sphere;

// Draw 2D Circle
void DrawCircle2D(Circle circle);
// Draw 3D Circle
// Named mz_ because raylib function of DrawCircle3D();
void DrawSphere(Sphere circle);