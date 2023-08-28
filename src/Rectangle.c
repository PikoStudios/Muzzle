#include "shapes/Rectangle.h"
#include "internal/globals.internal.h"

#define DEFINE_QUAD_VERTEX(x, y, nt, tx, ty, tid) \
active->quad_vertex_ptr->position = (vec2){x,y}; \
active->quad_vertex_ptr->tint = nt; \
active->quad_vertex_ptr->texture_coordinate = (vec2){tx,ty}; \
active->quad_vertex_ptr->texture_id = tid; \
active->quad_vertex_ptr++


void draw_rectangle_rec(rectangle rec, tint color_drawn)
{
    batch* active = mz_globals_internal_active_batch;
    active->quad_count++;

    if (active->quad_count > MUZZLE_BATCH_QUAD_MAX)
    {
        end_batch(active);
        begin_batch(active);
    }

    vec4 normalized_tint = (vec4){color_drawn.r / 255, color_drawn.g / 255, color_drawn.b / 255, color_drawn.a / 255};

    // Vertex 1
    DEFINE_QUAD_VERTEX(
        rec.x + rec.width, rec.y + rec.height, /* Position */
        normalized_tint, /* Normalized Tint */
        0.0f, 0.0f, /* Texture Coordinate */
        0.0f /* Texture ID*/
    );

    // Vertex 2
    DEFINE_QUAD_VERTEX(
        rec.x + rec.width, rec.y, /* Position */
        normalized_tint, /* Normalized Tint */
        1.0f, 0.0f, /* Texture Coordinate */
        0.0f /* Texture ID*/
    );

    // Vertex 3
    DEFINE_QUAD_VERTEX(
        rec.x, rec.y, /* Position */
        normalized_tint, /* Normalized Tint */
        1.0f, 1.0f, /* Texture Coordinate */
        0.0f /* Texture ID */
    );

    // Vertex 4
    DEFINE_QUAD_VERTEX(
        rec.x, rec.y + rec.width, /* Position */
        normalized_tint, /* Normalized Tint */
        0.0f, 1.0f, /* Texture Coordinate */
        0.0f /* Texture ID */
    );
}

void draw_rectangle_vec2(vec2 position, vec2 size, tint color_drawn)
{
    draw_rectangle_rec((rectangle){position.x, position.y, size.x, size.y}, color_drawn);
}

void draw_rectangle(float x, float y, float width, float height, tint color_drawn)
{
    draw_rectangle_rec((rectangle){x, y, width, height}, color_drawn);
}