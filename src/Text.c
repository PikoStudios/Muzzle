#include "core/Text.h"


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

MZ_API void unload_font(font font_used)
{
    glfonsDelete(font_used.context);
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


void draw_blurred_text(font font_used, const char *text, float x, float y, float intensity, float font_size, tint color_drawn)
{
    unsigned int col = glfonsRGBA(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);

    fonsClearState(font_used.context);
    fonsSetFont(font_used.context, font_used.fn);

    fonsSetSize(font_used.context, font_size);
    fonsSetColor(font_used.context, col);
    fonsSetSpacing(font_used.context, 5.f);
    fonsSetBlur(font_used.context, intensity);
    fonsDrawText(font_used.context, x, y+font_size-6, text, NULL);
}

void draw_shadow_text(font font_used, const char *text, float x, float y, tint shadow_color, float intensity, float font_size, tint color_drawn)
{
    unsigned int textcol = glfonsRGBA(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);
    unsigned int shadowcol = glfonsRGBA(shadow_color.r, shadow_color.g, shadow_color.b, shadow_color.a);

    fonsClearState(font_used.context);
    fonsSetFont(font_used.context, font_used.fn);

    fonsSetSize(font_used.context, font_size);
    fonsSetColor(font_used.context, shadowcol);
    fonsSetSpacing(font_used.context, .0f);
    fonsSetBlur(font_used.context, intensity);
    fonsDrawText(font_used.context, x, y+font_size-6, text, NULL);

    fonsSetColor(font_used.context, textcol);
    fonsSetBlur(font_used.context, 0);
    fonsDrawText(font_used.context, x, y+font_size-6, text, NULL);
}

void draw_blurred_text_vec2(font font_used, const char *text, vec2 position, float intensity, float font_size, tint color_drawn)
{
    draw_blurred_text(font_used, text, position.x, position.y, intensity, font_size, color_drawn);
}

void draw_shadow_text_vec2(font font_used, const char *text, vec2 position, tint shadow_color, float intensity, float font_size, tint color_drawn)
{
    draw_shadow_text(font_used, text, position.x, position.y, shadow_color, intensity, font_size, color_drawn);
}