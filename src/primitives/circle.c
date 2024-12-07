#include "primitives/circle.h"
#include "backend.h"
#include "core/circle_renderer.h"

#define TINT_TO_VEC4(t) (mz_vec4){(float)(t.r),(float)(t.g),(float)(t.b), (float)(t.a)}
#define VERTEX(x, y, cxy, t, r, ro) (struct mz_circle_vertex){(mz_vec2){x,y}, cxy, t, r, ro}

void mz_draw_circle(mz_applet* applet, float x, float y, float radius, mz_tint tint)
{
	MZ_TRACK_FUNCTION();
	applet->render_order++;

	mz_vec4 color = TINT_TO_VEC4(tint);
	mz_vec2 center = (mz_vec2){x, y};
	struct mz_circle_vertex v1 = VERTEX(x - radius, y + radius, center, color, radius, applet->render_order);
	struct mz_circle_vertex v2 = VERTEX(x + radius, y + radius, center, color, radius, applet->render_order);
	struct mz_circle_vertex v3 = VERTEX(x - radius, y - radius, center, color, radius, applet->render_order);
	struct mz_circle_vertex v4 = VERTEX(x + radius, y - radius, center, color, radius, applet->render_order);

	if (mz_circle_renderer_push_circle(&applet->circle_renderer, v1, v2, v3, v4) == MUZZLE_FALSE)
	{
		mz_circle_renderer_flush(&applet->circle_renderer, applet->width, applet->height);
#ifdef MUZZLE_DEBUG_BUILD
		MZ_ASSERT_DETAILED(mz_circle_renderer_push_circle(&applet->circle_renderer, v1, v2, v3, v4) == MUZZLE_TRUE, "If circle renderer is still full after flushing, there has been a bug")
#else
		mz_circle_renderer_push_circle(&applet->circle_renderer, v1, v2, v3, v4);
#endif
	}
}

void mz_draw_circle_vec2(mz_applet* applet, mz_vec2 center, float radius, mz_tint tint)
{
	mz_draw_circle(applet, center.x, center.y, radius, tint);
}

void mz_draw_circle_vec3(mz_applet* applet, mz_vec3 center_and_radius, mz_tint tint)
{
	mz_draw_circle(applet, center_and_radius.x, center_and_radius.y, center_and_radius.z, tint);
}

void mz_draw_circle_type(mz_applet* applet, mz_circle circle, mz_tint tint)
{
	mz_draw_circle(applet, circle.x, circle.y, circle.radius, tint);
}
