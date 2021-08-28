#include "core/Text.h"

font load_font_fs(const char* filepath, font_manager* manager, const char* name)
{
    int fn = fonsAddFont(manager, name, filepath);

    if (fn == -1)
    {
        log_status(STATUS_FATAL_ERROR, "Failed to load Font :: Point of Failure\n\tMUZZLE::TEXT::LOAD_FONT");
    }

    return (font) {fn, manager};
}

font load_font(const char* filepath, const char* name)
{
    FONScontext* context = glfonsCreate(512, 512, FONS_ZERO_TOPLEFT);
    int fn = fonsAddFont(context, name, filepath);


    if (fn == -1)
    {
        log_status(STATUS_FATAL_ERROR, "Failed to load Font :: Point of Failure\n\tMUZZLE::TEXT::LOAD_FONT");
    }

    return (font) {fn, context};
}

void draw_text(font font_used, const char *text, float x, float y, float font_size, tint color_drawn)
{
    unsigned int col = glfonsRGBA(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);

    fonsClearState(font_used.context);
    fonsSetFont(font_used.context, font_used.fn);

    fonsSetSize(font_used.context, font_size);
    fonsSetColor(font_used.context, col);
    fonsDrawText(font_used.context, x, y+font_size-6, text, NULL);
}

void draw_text_vec2(font font_used, const char *text, vec2 pos, float font_size, tint color_drawn)
{
    draw_text(font_used, text, pos.x, pos.y, font_size, color_drawn);
}


void draw_text_fs(font font_used, const char *text, float x, float y, float font_size, tint color_drawn, font_manager* manager)
{
    unsigned int col = glfonsRGBA(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);

    fonsClearState(manager);
    fonsSetFont(manager, font_used.fn);

    fonsSetSize(manager, font_size);
    fonsSetColor(manager, col);
    fonsDrawText(manager, x, y+font_size-6, text, NULL);
}

void draw_text_vec2_fs(font font_used, const char *text, vec2 pos, float font_size, tint color_drawn, font_manager* manager)
{
    draw_text_fs(font_used, text, pos.x, pos.y, font_size, color_drawn, manager);
}

const char char_f(const char* text)
{
    sprintf(__char_f_buffer, text);
    return __char_f_buffer;
}

const char get_engine_char_f_buffer()
{
    return __char_f_buffer;
}