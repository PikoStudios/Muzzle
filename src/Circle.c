#include "shapes/Circle.h"

void DrawCircle2D(Circle circle)
{
    DrawCircle(circle.CenterX, circle.CenterY, circle.radius, circle.tint);
}

void mz_DrawCircle3D(Sphere circle)
{
    DrawCircle3D(circle.center, circle.radius, circle.RotationAxis, circle.RotationAngle, circle.tint);
}