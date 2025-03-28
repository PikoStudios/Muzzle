#include "core/applet.h"
#include "backend.h"
#include "core/logging.h"
#include "core/shader.h"

#include "core/quad_renderer.h"
#include "core/circle_renderer.h"
#include "core/text_renderer.h"

#include "core/shaders/default_shaders.h"

#include "internals/gl_callbacks.h"
#include "internals/glfw_callbacks.h"
#include "internals/glfw_error_helper.h"

static inline void create_framebuffer(mz_applet* applet, int i)
{
	glGenFramebuffers(1, &applet->framebuffer.fbos[i]);
	glBindFramebuffer(GL_FRAMEBUFFER, applet->framebuffer.fbos[i]);

	glGenTextures(1, &applet->framebuffer.textures[i]);
	glBindTexture(GL_TEXTURE_2D, applet->framebuffer.textures[i]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, applet->width, applet->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, applet->framebuffer.textures[i], 0);

	glGenRenderbuffers(1, &applet->framebuffer.depth_buffers[i]);
	glBindRenderbuffer(GL_RENDERBUFFER, applet->framebuffer.depth_buffers[i]);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, applet->width, applet->height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, applet->framebuffer.depth_buffers[i]);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Could not create framebuffer");
	}
}

mz_applet mz_initialize_applet(const char* window_title, int width, int height, mz_applet_flags flags)
{
	MZ_TRACK_FUNCTION();

	mz_applet applet;
	applet.width = width;
	applet.height = height;
	applet.shader_passes_len = 0;

	if (!glfwInit())
	{
		const char* error_description = internals_get_error_description();
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "GLFW3 failed to initialize:\n\t%s", error_description);
	}

	mz_log_status(LOG_STATUS_SUCCESS, "Successfully initialized GLFW3");

	int result = FT_Init_FreeType(&applet.font_library);
	
	if (result != 0)
	{
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Freetype failed to initialize, error code: %d", result);
	}

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

	applet.delta_time = (flags & APPLET_FLAG_TRACK_DELTA_TIME) ? 0.0f : -1;

	glfwSetWindowPos(applet.window, 230, 230); // TODO: needed?

#ifdef MUZZLE_DEBUG_BUILD
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(internals_gl_debug_message_callback, NULL);
#endif

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Initialize off-screen framebuffer (used by shader passes)
	create_framebuffer(&applet, 0);
	create_framebuffer(&applet, 1);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glGenVertexArrays(1, &applet.framebuffer.vao);
	glGenBuffers(1, &applet.framebuffer.vbo);

	glBindVertexArray(applet.framebuffer.vao);
	glBindBuffer(GL_ARRAY_BUFFER, applet.framebuffer.vbo);

	GLfloat shader_pass_vertices[] =
	{
		// vec2 aScreenCoords, vec2 aTexCoords
		-1.0f,1.0f, 0.0f,1.0f,
		1.0f,1.0f, 1.0f,1.0f,
		-1.0f,-1.0f, 0.0f,0.0f,
		1.0f,1.0f, 1.0f,1.0f,
		-1.0f,-1.0f, 0.0f,0.0f,
		1.0f,-1.0f, 1.0f,0.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(shader_pass_vertices), shader_pass_vertices, GL_STATIC_DRAW);

	glEnableVertexArrayAttrib(applet.framebuffer.vao, 0);
	glVertexAttribPointer(
		0,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(GLfloat) * 4,
		0
	);

	glEnableVertexArrayAttrib(applet.framebuffer.vao, 1);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(GLfloat) * 4,
		(void*)(sizeof(GLfloat) * 2)
	);

	mz_shader default_quad_shader = mz_create_shader((char*)(quad_vertex_glsl), (char*)(quad_fragment_glsl), SHADER_TYPE_DIRECT_QUAD);
	mz_shader default_sprite_shader = mz_create_shader((char*)(sprite_vertex_glsl), (char*)(sprite_fragment_glsl), SHADER_TYPE_DIRECT_SPRITE);
	mz_shader default_circle_shader = mz_create_shader((char*)(circle_vertex_glsl), (char*)(circle_fragment_glsl), SHADER_TYPE_DIRECT_CIRCLE);
	mz_shader default_text_shader = mz_create_shader((char*)(text_vertex_glsl), (char*)(text_fragment_glsl), SHADER_TYPE_DIRECT_TEXT);

	mz_log_status(LOG_STATUS_SUCCESS, "Compiled default shaders");

	applet.render_order = 0;

	applet.quad_renderer = mz_quad_renderer_initialize(MUZZLE_QUAD_BUFFER_CAPACITY);
	applet.sprite_renderer = mz_sprite_renderer_initialize(MUZZLE_SPRITE_BUFFER_CAPACITY);
	applet.circle_renderer = mz_circle_renderer_initialize(MUZZLE_CIRCLE_BUFFER_CAPACITY);
	applet.text_renderer = mz_text_renderer_initialize(MUZZLE_TEXT_BUFFER_CAPACITY);
	
	applet.quad_renderer.shader_id = default_quad_shader.pid;
	applet.sprite_renderer.shader_id = default_sprite_shader.pid;
	applet.circle_renderer.shader_id = default_circle_shader.pid;
	applet.text_renderer.shader_id = default_text_shader.pid;


	applet.quad_renderer.default_shader_id = default_quad_shader.pid;
	applet.sprite_renderer.default_shader_id = default_sprite_shader.pid;
	applet.circle_renderer.default_shader_id = default_circle_shader.pid;
	applet.text_renderer.default_shader_id = default_text_shader.pid;
	
	return applet;
}

void mz_start_applet(mz_applet* applet, mz_applet_main_dispatch_fn main_dispatch)
{
	glfwSetWindowUserPointer(applet->window, applet);
	main_dispatch(applet);
}

mz_boolean mz_keep_applet(mz_applet* applet)
{
	if (applet->delta_time > -1)
	{
		applet->delta_time = glfwGetTime();
		glfwSetTime(0);
	}

	return !glfwWindowShouldClose(applet->window);
}

void mz_terminate_applet(mz_applet* applet)
{
	MZ_TRACK_FUNCTION();

	mz_log_status(LOG_STATUS_INFO, "Cleaning up resources");
	
	glDeleteFramebuffers(2, applet->framebuffer.fbos);
	glDeleteTextures(2, applet->framebuffer.textures);
	glDeleteRenderbuffers(2, applet->framebuffer.depth_buffers);
	glDeleteVertexArrays(1, &applet->framebuffer.vao);
	glDeleteBuffers(1, &applet->framebuffer.vbo);

	mz_quad_renderer_destroy(&applet->quad_renderer);
	mz_sprite_renderer_destroy(&applet->sprite_renderer);
	mz_circle_renderer_destroy(&applet->circle_renderer);
	mz_text_renderer_destroy(&applet->text_renderer);

	mz_log_status(LOG_STATUS_INFO, "Closing Window");
	
	glfwDestroyWindow(applet->window);
	glfwTerminate();
}

void mz_update_window_title(mz_applet* applet, const char* title)
{
	glfwSetWindowTitle(applet->window, title);
}
