#include "primitives/rectangle.h"
#include "backend.h"
#include "core/quad_renderer.h"
#include <stdio.h>

#define TINT_TO_VEC4(t) (mz_vec4){(float)(t.r),(float)(t.g),(float)(t.b), (float)(t.a)}
#define VERTEX(x,y,t, ro) (struct mz_quad_vertex){(mz_vec2){x,y}, t, ro}
#define UNLIKELY_IF(x) if (__builtin_expect(!!(x), 0))

void mz_draw_rectangle(mz_applet* applet, float x, float y, float width, float height, mz_tint tint)
{
	MZ_TRACK_FUNCTION();

	applet->render_order++;
	
	mz_vec4 color = TINT_TO_VEC4(tint);
	struct mz_quad_vertex v1 = VERTEX(x, y, color, applet->render_order);
	struct mz_quad_vertex v2 = VERTEX(x + width, y, color, applet->render_order);
	struct mz_quad_vertex v3 = VERTEX(x, y + height, color, applet->render_order);
	struct mz_quad_vertex v4 = VERTEX(x + width, y + height, color, applet->render_order);
	
	if (mz_quad_renderer_push_quad(&applet->quad_renderer, v1, v2, v3, v4) == MUZZLE_FALSE)
	{
		// Quad renderer is full
		mz_quad_renderer_flush(&applet->quad_renderer, applet->width, applet->height);
#ifdef MUZZLE_DEBUG_BUILD
		MZ_ASSERT_DETAILED(mz_quad_renderer_push_quad(&applet->quad_renderer, v1, v2, v3, v4) == MUZZLE_TRUE, "If quad renderer is still full after flushing, there has been a bug")
#else
		mz_quad_renderer_push_quad(&applet->quad_renderer, v1, v2, v3, v4);
#endif
	}
}

void mz_draw_rectangle_vec2(mz_applet* applet, mz_vec2 position, mz_vec2 size, mz_tint tint)
{
	mz_draw_rectangle(applet, position.x, position.y, size.x, size.y, tint);
}

void mz_draw_rectangle_type(mz_applet* applet, mz_rectangle rec, mz_tint tint)
{
	mz_draw_rectangle(applet, rec.x, rec.y, rec.width, rec.height, tint);
}
