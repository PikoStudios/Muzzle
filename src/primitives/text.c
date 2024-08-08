#include "primitives/text.h"
#include "core/font.h"
#include "core/logging.h"
#include "core/text_renderer.h"
#include "core/vector.h"

#define TINT_TO_VEC4(t) (mz_vec4){(float)(t.r),(float)(t.g),(float)(t.b), (float)(t.a)}
#define VERTEX(x, y, tx, ty, tidx) (struct mz_text_vertex){(mz_vec2){x, y}, (mz_vec2){tx, ty}, tidx}
#define UNLIKELY_IF(x) if (__builtin_expect(!!(x), 0))

static inline mz_font_glyph safe_index_glyphs(mz_font* font, unsigned int index)
{
	return (index >= font->glyph_count) ? (mz_font_glyph){0} : font->glyphs[index];
}

void mz_draw_text(mz_applet* applet, const char* text, float x, float y, float font_size, mz_font* font, mz_tint tint)
{
	applet->render_order++;
	
	mz_vec4 color = TINT_TO_VEC4(tint);
	float scale = font_size / 256;
	float newline_x = x;

	for (int i = 0; text[i] != '\0'; i++)
	{
		int idx = text[i];
		mz_font_glyph glyph;
		
load_char:
		glyph = safe_index_glyphs(font, idx); // NOTE: Reason we do this is because we can't declare a variable, goto, declare it again.

		UNLIKELY_IF(glyph._loaded == MUZZLE_FALSE)
		{
			mz_log_status_formatted(LOG_STATUS_WARNING, "Unloaded character: '%c'", text[i]);

			if (idx == ' ')
			{
				// NOTE: This is to prevent an infinite loop where we keep trying to load the space glyph and its unloaded
				x += MUZZLE_TEXT_DEFAULT_SPACE_WIDTH * scale;
				continue;
			}
			
			idx = ' ';
			goto load_char;
		}

		if (text[i] == '\n')
		{
			y += glyph.size.y * /* 1.3 * */ scale;
			x = newline_x;
			continue;
		}

		if (text[i] == ' ')
		{
			// No need to render a space. Just advance to next character
			goto advance;
		}

		mz_vec2 pos = (mz_vec2){x + glyph.bearing.x * scale, y - glyph.bearing.y * scale};
		int size = 256 * scale;

		struct mz_text_vertex v1 = VERTEX(pos.x, pos.y, 0, 0, glyph.texture_idx);
		struct mz_text_vertex v2 = VERTEX(pos.x + size, pos.y, 1, 0, glyph.texture_idx);
		struct mz_text_vertex v3 = VERTEX(pos.x, pos.y + size, 0, 1, glyph.texture_idx);
		struct mz_text_vertex v4 = VERTEX(pos.x + size, pos.y + size, 1, 1, glyph.texture_idx);

		if (mz_text_renderer_push_char(&applet->text_renderer, v1, v2, v3, v4) == MUZZLE_FALSE)
		{
			mz_text_renderer_flush(&applet->text_renderer, font, applet->width, applet->height, applet->render_order, color);
#ifdef MUZZLE_DEBUG_BUILD
			MZ_ASSERT_DETAILED(mz_text_renderer_push_char(applet->text_renderer, v1, v2, v3, v4) == MUZZLE_TRUE, "Text renderer should be empty");
#else
			mz_text_renderer_push_char(&applet->text_renderer, v1, v2, v3, v4);
#endif
		}

advance:
		// bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		x += (glyph.advance >> 6) * scale;
	}
	
	mz_text_renderer_flush(&applet->text_renderer, font, applet->width, applet->height, applet->render_order, color);
}

void mz_draw_text_vec2(mz_applet* applet, const char* text, mz_vec2 position, float font_size, mz_font* font, mz_tint tint)
{
	
}

void mz_draw_text_vec3(mz_applet* applet, const char* text, mz_vec3 position_and_font_size, mz_font* font, mz_tint tint)
{
	
}
