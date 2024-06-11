#include "core/applet.h"
#include "core/logging.h"
#include "core/quad_renderer.h"
#include "core/shader.h"
#include "internals/glfw_callbacks.h"
#include "internals/glfw_error_helper.h"
#include "core/shaders/quad_renderer_default_vertex.glsl.h"
#include "core/shaders/quad_renderer_default_fragment.glsl.h"

mz_applet mz_initialize_applet(const char* window_title, int width, int height, mz_applet_flags flags)
{
	mz_applet applet;
	applet.width = width;
	applet.height = height;

	if (!glfwInit())
	{
		const char* error_description = internals_get_error_description();
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "GLFW3 failed to initialize:\n\t%s", error_description);
	}

	mz_log_status(LOG_STATUS_SUCCESS, "Successfully initialized GLFW3");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MUZZLE_OPENGL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MUZZLE_OPENGL_VERSION_MINOR);

	glfwSetErrorCallback(internals_glfw_callback_error);

	applet.window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	if (applet.window == NULL)
	{
		const char* error_description = internals_get_error_description();
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "GLFW3 Window failed to initialized: \n\t%s", error_description);
	}

	mz_log_status(LOG_STATUS_SUCCESS, "Successfully created window");

	glfwSetFramebufferSizeCallback(applet.window, internals_glfw_callback_window_resize);
	glfwSetKeyCallback(applet.window, internals_glfw_callback_key);
	glfwMakeContextCurrent(applet.window);

	if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)))
	{
		glfwDestroyWindow(applet.window);
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "GLAD failed to initialize");
	}

	glfwSwapInterval(0);
	glfwSetWindowAttrib(applet.window, GLFW_RESIZABLE, (flags & APPLET_FLAG_RESIZBALE));

	if (flags & APPLET_FLAG_VSYNC)
	{
		mz_log_status(LOG_STATUS_INFO, "Enabled VSync");
		glfwSwapInterval(1);
	}

	applet.delta_time = 0.0f;
	applet.delta_time_flag = MZ_BOOLEAN_CAST(flags & APPLET_FLAG_TRACK_DELTA_TIME);

	glfwSetWindowPos(applet.window, 230, 230); // TODO: needed?

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mz_shader default_quad_shader = mz_create_shader((char*)(quad_renderer_default_vertex_glsl), (char*)(quad_renderer_default_fragment_glsl), SHADER_TARGET_QUAD); 

	applet.render_order = 0;
	applet.quad_renderer = mz_quad_renderer_initialize(100); // TODO: Macro instead of hard coded value
	applet.quad_renderer.shader_id = default_quad_shader.pid;
	
	return applet;
}

void mz_start_applet(mz_applet* applet, mz_applet_main_dispatch_fn main_dispatch)
{
	glfwSetWindowUserPointer(applet->window, applet);
	main_dispatch(applet);
}

mz_boolean mz_keep_applet(mz_applet* applet)
{
	if (applet->delta_time_flag)
	{
		applet->delta_time = glfwGetTime();
		glfwSetTime(0);
	}

	return !glfwWindowShouldClose(applet->window);
}

void mz_terminate_applet(mz_applet* applet)
{
	mz_log_status(LOG_STATUS_INFO, "Cleaning up resources");
	mz_quad_renderer_destroy(&applet->quad_renderer);
	
	mz_log_status(LOG_STATUS_INFO, "Closing Window");
	glfwDestroyWindow(applet->window);
	glfwTerminate();
}
