#include "shapes/Rectangle.h"

void draw_rectangle(int x, int y, int width, int height, tint color_drawn)
{
    #ifdef MUZZLE_RETAIN_LEGACY
        glBegin(GL_QUADS);
            glColor4ub(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);
            glVertex2i(x, y);
            glVertex2i(x + width, y);
            glVertex2i(x + width, y + height);
            glVertex2i(x, y + height);
        glEnd();
    #else
        #warning "Not Implemented"
    #endif
}
void draw_rectangle_rec(Applet* applet, rectangle* rec, tint color_drawn)
{
    if (rec->index == 0)
    {
        rec->parent = applet->rect_batchers.length - 1;
        rec->index = applet->rect_batchers.batchers[rec->parent].object_count++;
        
        if (applet->rect_batchers.batchers[rec->parent].object_count > applet->rect_batchers.batchers[rec->parent].max_size)
        {
            // TODO: Implement this behaviour
        }
    }
    
    // TODO: Profile this if slow
    update_batcher_rectangle(&applet->rect_batchers.batchers[rec->parent], rec->index, rec->x, rec->y, rec->width, rec->height, color_drawn);
    
    #ifdef MUZZLE_RETAIN_LEGACY
        glBegin(GL_QUADS);
            glColor4ub(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);
            glVertex2i(rec.x, rec.y);
            glVertex2i(rec.x + rec.width, rec.y);
            glVertex2i(rec.x + rec.width, rec.y + rec.height);
            glVertex2i(rec.x, rec.y + rec.height);
        glEnd();
    #endif
}
void draw_rectangle_vec2(vec2 pos, vec2 size, tint color_drawn)
{
    #ifdef MUZZLE_RETAIN_LEGACY
        glBegin(GL_QUADS);
            glColor4ub(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);
            glVertex2f(pos.x, pos.y);
            glVertex2f(pos.x + size.x, pos.y);
            glVertex2f(pos.x + size.x, pos.y + size.y);
            glVertex2f(pos.x, pos.y + size.y);
        glEnd();
    #else
        #warning "Not Implemented"
    #endif
}