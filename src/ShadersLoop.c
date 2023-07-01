#include "modern_pipeline/ShadersLoop.h"

void begin_shader(Applet* applet, shader_program shader, geometry_type type)
{
	end_batcher(&applet->batch);
	
	switch(type)
	{
	case GEOMETRY_QUAD:
		applet->batch.quad_shader = shader;
		break;
	case GEOMETRY_CIRCLE:
		applet->batch.circle_shader = shader;
		break;
	case GEOMETRY_LINE:
		applet->batch.line_shader = shader;
		break;
	case GEOMETRY_ALL:
		applet->batch.quad_shader = shader;
		applet->batch.circle_shader = shader;
		applet->batch.line_shader = shader;
		break;
	default:
		break;
	}
	
	begin_batcher(&applet->batch);
}

void end_shader(Applet* applet, shader_program shader, geometry_type type)
{
	end_batcher(&applet->batch);
	
}