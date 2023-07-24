#include "core/Applet.h"
#include "internal/core.internal.h"
#include "internal/core.default_shaders.internal.h"

Applet InitializeApplet(int width, int height, const char* window_title, uint32_t flags)
{
	// TODO: Downgrade to OpenGL 3.3 as we aren't using any OpenGL 4.x features
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	
	glfwSetErrorCallback(mz_glfw_callback_error);
	
	if (!glfwInit()) log_status(STATUS_FATAL_ERROR_DONT_CLEAN_UP, "GLFW3 could not initialize");
	log_status(STATUS_SUCCESS, "GLFW3 Initialized Successfully");
	
	Applet applet;
	applet.height = height;
	applet.width = width;
	applet.window_title = (char*)(window_title);
	applet.window_handle = glfwCreateWindow(width, height, window_title, NULL, NULL);
	
	if (applet.window_handle == NULL)
	{
		glfwTerminate();
		log_status(STATUS_FATAL_ERROR, "GLFW3 Could not create the window");
	}
	
	log_status(STATUS_SUCCESS, "Window created successfully");
	
	glfwSetFramebufferSizeCallback(applet.window_handle, mz_glfw_callback_window_resize);
	glfwSetKeyCallback(applet.window_handle, mz_glfw_callback_key);
	glfwMakeContextCurrent(applet.window_handle);
	
	if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)))
	{
		glfwDestroyWindow(applet.window_handle);
		log_status(STATUS_FATAL_ERROR, "GLAD could not initialize");
	}
	
	if (flags & APPLET_VSYNC)
	{
		log_status(STATUS_INFO, "Enabled VSync");
		glfwSwapInterval(1);
	}
	else
	{
		log_status(STATUS_WARNING, "VSync was not enabled. This could cause high CPU/GPU Usage");
		glfwSwapInterval(0);
	}
	
	glfwSetWindowAttrib(applet.window_handle, GLFW_RESIZABLE, (flags & APPLET_RESIZABLE));
	glfwSetWindowPos(applet.window_handle, 230, 230);
	
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	applet.default_fragment = mz_load_default_shader_fragment();
	applet.default_vertex = mz_load_default_shader_vertex();
	applet.default_shader_program = link_shader(applet.default_vertex, applet.default_fragment);
	applet.default_batch = load_batch(applet.default_shader_program);
	applet.active_batch = &applet.default_batch;
	
	return applet;
}

void StartApplet(Applet* self)
{
	glfwSetWindowUserPointer(self->window_handle, self);
	OnAppletUpdate(self);
}

mz_boolean keep_applet(Applet* self)
{
	return !glfwWindowShouldClose(self->window_handle);
}

mz_boolean keep_applet_delta(Applet* self, double* delta)
{
	*delta = glfwGetTime();
	glfwSetTime(0);
	return !glfwWindowShouldClose(self->window_handle);
}

mz_boolean keep_applet_delta_f(Applet* self, float* delta)
{
	*delta = (float)(glfwGetTime());
	glfwSetTime(0);
	return !glfwWindowShouldClose(self->window_handle);
}

void QuitMuzzle(Applet* self)
{
	log_status(STATUS_INFO, "Closing Window");
	glfwDestroyWindow(self->window_handle);
	
	log_status(STATUS_INFO, "Unloading resources");
	unload_batch(&self->default_batch);
	unload_shader_program(&self->default_shader_program);
	unload_shader(&self->default_fragment);
	unload_shader(&self->default_vertex);
	
	log_status(STATUS_INFO, "Terminating OpenGL Context");
	glfwTerminate();
}