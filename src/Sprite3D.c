#include "textures/Sprite3D.h"

void DrawSprite3D(Sprite3D sprite, Camera camera)
{
    DrawBillboard(camera, sprite.texture, sprite.position, sprite.size, sprite.tint);
}
