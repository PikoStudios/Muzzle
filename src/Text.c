#include "core/Text.h"

font load_font(const char* filepath, font_manager* manager, const char* name)
{
   int fn = fonsAddFont(manager, name, filepath);

    if (fn == -1)
    {
        log_status(STATUS_FATAL_ERROR, "Failed to load Font :: Point of Failure\n\tMUZZLE::TEXT::LOAD_FONT");
    }

    return fn;
}

void draw_text(font font_used, const char *text, float x, float y, float font_size, tint color_drawn, font_manager* manager)
{
    unsigned int col = glfonsRGBA(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);

    fonsClearState(manager);
    fonsSetFont(manager, font_used);

    fonsSetSize(manager, font_size);
    fonsSetColor(manager, col);
    fonsDrawText(manager, x, y+font_size-6, text, NULL);
}

void draw_text_vec2(font font_used, const char *text, vec2 pos, float font_size, tint color_drawn, font_manager* manager)
{
    draw_text(font_used, text, pos.x, pos.y, font_size, color_drawn, manager);
}