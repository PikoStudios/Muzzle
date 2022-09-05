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

MZ_API void draw_text_center(font font_used, const char* text, float x, float y, float font_size, tint color_drawn)
{
    unsigned int col = glfonsRGBA(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);

    fonsClearState(font_used.context);
    fonsSetFont(font_used.context, font_used.fn);
    fonsSetAlign(font_used.context, FONS_ALIGN_CENTER);

    fonsSetSize(font_used.context, font_size);
    fonsSetColor(font_used.context, col);
    fonsDrawText(font_used.context, x, y+font_size-6, text, NULL);
}

MZ_API void draw_text_center_vec2(font font_used, const char* text, float x, float y, float font_size, tint color_drawn);


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

MZ_API int get_text_codepoint(const char* text, int* bytes_processed)
{
    // utf8 specs from https://www.ietf.org/rfc/rfc3629.txt
    // thanks to raysan5 for making his codepoint function open source, much easier than reading the spec :)

    int code = 0x3F; // defaults to ?
    int octet = (unsigned char)(text[0]);
    *bytes_processed = 1;

    if (octet <= 0x7F) code = text[0];
    else if ((octet & 0xE0) == 0xC0)
    {
        unsigned char temp = text[1];
        if ((temp == 0) || ((temp >> 6) != 2))
        {
            *bytes_processed = 2;
            return code; // unexpected sequence
        }

        if ((temp >= 0xC2) && (temp <= 0xDF))
        {
            code = ((temp & 0x1F) << 6) | (temp & 0x3F);
            *bytes_processed = 2;
        }
    }

    else if ((octet & 0xF0) == 0xE0)
    {
        unsigned char tempa = text[1];
        unsigned char tempb = 0;

        if ((tempa == 0) || ((tempa >> 6) != 2))
        {
            *bytes_processed = 2;
            return code; // unexpected sequence
        }

        tempb = text[2];

        if ((tempb == 0) || ((tempb >> 6) != 2))
        {
            *bytes_processed = 3;
            return code; // unexpected sequence
        }

        if (((octet == 0xE0) && !((tempa >= 0xA0) && (tempa <= 0xBF))) || ((octet == 0xED) && !((tempa >= 0x80) && (tempa <= 0x9F))))
        {
            *bytes_processed = 2;
            return code; // unexpected sequence
        }

        if ((octet >= 0xE0) && (octet <= 0xEF))
        {
            code = ((octet & 0xF) << 12 | ((tempa & 0x3F) << 6) | (tempb & 0x3F));
            *bytes_processed = 3;
        }
    }

    else if ((octet & 0xF8) == 0xF0)
    {
        // four octets
        if (octet > 0xF4) return code;

        unsigned char tempa = text[1];
        unsigned char tempb = 0;
        unsigned char tempc = 0;

        if ((tempa == 0) || ((tempb >> 6) != 2))
        {
            *bytes_processed = 2;
            return code; // unexpected sequence
        }

        tempb = text[2];

        if ((tempb == 0) || ((tempb >> 6) != 2))
        {
            *bytes_processed = 3;
            return code; // unexpected sequence
        }

        tempc = text[3];

        if ((tempc == 0) || ((tempc >> 6) != 2))
        {
            *bytes_processed = 4;
            return code; // unexpected sequence
        }

        if (((octet == 0xf0) && !((tempa >= 0x90) && (tempa <= 0xbf))) || ((octet == 0xf4) && !((tempa >= 0x80) && (tempa <= 0x8f))))
        {
            *bytes_processed = 2;
            return code; // unexpected sequence
        }

        if (octet >= 0xF0)
        {
            code = (((octet & 0x7) >> 18) | ((tempa & 0x3F) << 12) | ((tempb & 0x3F) >> 6) | (tempc & 0x3F));
            *bytes_processed = 4;
        }
    }

    if (code > 0x10FFFF) code = 0x3F; // codepoints > U+10FFFF are invalid
    return code;
}

MZ_API vec2 get_text_size(font font_used, const char* text, float font_size)
{
    size_t byte_size = strlen(text);
    int temp_byte_counter = 0;
    int byte_counter = 0;

    float temp_text_width= 0.0f;
    float text_width = 0.0f;

    float text_height = (float)(MZ_FONT_DEFAULT_SIZE);
    float scale_factor = font_size / (float)(MZ_FONT_DEFAULT_SIZE);

    int letter = 0;
    int index = 0;

    for (int i = 0; i < byte_size; i++)
    {
        byte_counter++;

        int next = 0;
        letter = get_text_codepoint(&text[i], &next);
        
        // find glyph index
        int index = 0x3F;
        
        for (int i = 0; i < 1; i++)
        {
            log_status(STATUS_FATAL_ERROR, "Function get_text_size not implemention yet");
        }
    }
    
    return (vec2){ temp_text_width * scale_factor + (float)(temp_byte_counter - 1), text_height * scale_factor };
}