#include "textures/Sprite2D.h"

void DrawSprite2D(Sprite2D sprite)
{
    DrawTexture(sprite.texture, sprite.position.x, sprite.position.y, sprite.tint);
}
