#include "core/Sprite.h"

sprite load_sprite(const char *filepath)
{
    int w,h,bpp;

    unsigned char *data = stbi_load(filepath, &w, &h, &bpp, 4);

    if (data == NULL) log_status(STATUS_ERROR, "Failed to load sprite");

    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);


    // Make texture repeat on axis, and add filter for pixel-perfect drawing
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

#ifdef MUZZLE_VERBOSE
    log_status(STATUS_SUCCESS, "Loaded Sprite into GPU");
#endif

    stbi_image_free(data);

    return (sprite)
    {
        .sprite_id = id,
        .width = w,
        .height = h,
    };
}

// sprite *load_sprite_ptr(const char *filepath)
// {
//     int w,h,bpp;

//     unsigned char *data = stbi_load(filepath, &w, &h, &bpp, 4);

//     if (data == NULL) log_status(STATUS_ERROR, "Failed to load sprite");

//     GLuint id;
//     glGenTextures(1, &id);
//     glBindTexture(GL_TEXTURE_2D, id);


//     // Make texture repeat on axis, and add filter for pixel-perfect drawing
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

// #ifdef MUZZLE_VERBOSE
//     log_status(STATUS_SUCCESS, "Loaded Sprite into GPU");
// #endif

//     stbi_image_free(data);

//     return (sprite *)
//     {
//         .sprite_id = id,
//         .width = w,
//         .height = h,
//     };
// }

void unload_sprite(sprite *data)
{
    glDeleteTextures(1, &data->sprite_id);
}
void draw_sprite(sprite *data, int x, int y, float scale, float rotation, tint color_drawn)
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, data->sprite_id);

    glPushMatrix();
        glTranslatef(x,y,0);
        glScalef(scale, scale, 1.0f);
        glRotatef(rotation, 0,0,1.0f);

        glBegin(GL_QUADS);
            glColor4ub(color_drawn.r,color_drawn.g,color_drawn.b,color_drawn.a);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTexCoord2f(0.0f, 0.0f);glVertex2f(0.0f,0.0f);
            glTexCoord2f(1.0f, 0.0f);glVertex2f(data->width,0.0f);
            glTexCoord2f(1.0f, 1.0f);glVertex2f(data->width,data->height);
            glTexCoord2f(0.0f, 1.0f);glVertex2f(0.0f,data->height);
        glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void draw_sprite_vec2(sprite *data, vec2 pos, float scale, float rotation, tint color_drawn)
{
    draw_sprite(data, (int)(pos.x), (int)(pos.y), scale, rotation, color_drawn);
}

void draw_sprite_portion(sprite* data, rectangle rec, vec2 pos, tint color_drawn)
{
    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, data->sprite_id);

    glPushMatrix();
        glTranslatef(pos.x, pos.y, 0);

        glBegin(GL_QUADS);
            glColor4ub(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);
            glNormal3f(0.0f, 0.0f, 0.0f);
            glTexCoord2f((float)(rec.x / data->width), (float)(rec.y / data->height)); glVertex2f(0.0f, 0.0f);
            glTexCoord2f((float)((rec.x + rec.width) / data->width), (float)(rec.y / data->height)); glVertex2f(rec.width, 0.0f);
            glTexCoord2f((float)((rec.x + rec.width) / data->width), (float)((rec.y + rec.height) / data->height)); glVertex2f(rec.width, rec.height);
            glTexCoord2f((float)(rec.x / data->width), (float)((rec.y + rec.height) / data->height)); glVertex2f(0.0f, rec.height);
        glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}