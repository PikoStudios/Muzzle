#include "shapes/Rectangle.h"

void draw_rectangle(Applet* applet, int x, int y, int width, int height, tint color_drawn)
{
    draw_rectangle_vec2(applet, (vec2){x,y}, (vec2){width,height}, color_drawn);
}

void draw_rectangle_rec(Applet* applet, rectangle rec, tint color_drawn)
{
    draw_rectangle_vec2(applet, (vec2){rec.x,rec.y}, (vec2){rec.width,rec.height}, color_drawn);
}

void draw_rectangle_vec2(Applet* applet, vec2 pos, vec2 size, tint color_drawn)
{
    if (applet->batch.quads_count + 1 > applet->batch.max_size)
    {
        end_batcher(&applet->batch);
        begin_batcher(&applet->batch);
    }
    
    //static vec2 tex_coords[] = {{0.0f,0.0f}, {1.0f, 0.0f}, {1.0f,1.0f}, {0.0f, 1.0f}};
    
    // Vertex 1
    applet->batch.quads_current_ptr->position = (vec3){pos.x + size.x, pos.y + size.y, 1};
    applet->batch.quads_current_ptr->color_drawn = TINT_TO_TINTF(color_drawn);
    applet->batch.quads_current_ptr->tex_coords = (vec2){0.0f, 0.0f};
    applet->batch.quads_current_ptr->tex_id = 0.0f;
    applet->batch.quads_current_ptr++;
    
    // Vertex 2
    applet->batch.quads_current_ptr->position = (vec3){pos.x + size.x, pos.y, 1};
    applet->batch.quads_current_ptr->color_drawn = TINT_TO_TINTF(color_drawn);
    applet->batch.quads_current_ptr->tex_coords = (vec2){1.0f, 0.0f};
    applet->batch.quads_current_ptr->tex_id = 0.0f;
    applet->batch.quads_current_ptr++;
    
    // Vertex 3
    applet->batch.quads_current_ptr->position = (vec3){pos.x, pos.y, 1};
    applet->batch.quads_current_ptr->color_drawn = TINT_TO_TINTF(color_drawn);
    applet->batch.quads_current_ptr->tex_coords = (vec2){1.0f, 1.0f};
    applet->batch.quads_current_ptr->tex_id = 0.0f;
    applet->batch.quads_current_ptr++;
    
    // Vertex 4
    applet->batch.quads_current_ptr->position = (vec3){pos.x, pos.y + size.y, 1};
    applet->batch.quads_current_ptr->color_drawn = TINT_TO_TINTF(color_drawn);
    applet->batch.quads_current_ptr->tex_coords = (vec2){0.0f, 1.0f};
    applet->batch.quads_current_ptr->tex_id = 0.0f;
    applet->batch.quads_current_ptr++;
    
    applet->batch.quads_current_index += 4;
    applet->batch.quads_count++;
}