#include "core/Applet.h"

void __append_batchers(Applet* applet, int type)
{
    switch (type)
    {
    case BATCHER_TYPE_RECTANGLE:
        applet->rect_batchers.batchers = MZ_REALLOC(applet->rect_batchers.batchers, sizeof(batcher) * ++applet->rect_batchers.length);
        
        if (applet->rect_batchers.batchers == NULL)
            log_status(STATUS_FATAL_ERROR, "Not able to allocate enough memory to append rectangle batcher");

        applet->rect_batchers.batchers[applet->rect_batchers.length - 1] = create_batcher_rectangle(MZ_BATCHER_SIZE);
        applet->rect_batchers.top = &applet->rect_batchers.batchers[applet->rect_batchers.length - 1];
        
        break;
    }
}

void set_global_shader(Applet* applet, shader_program program)
{
    // Rectangle Batchers
    for (int i = 0; i < applet->rect_batchers.length; i++)
    {
        applet->rect_batchers.batchers[i].global_shader = program;
    }
}

void StartApplet(Applet* self)
{
    OnAppletUpdate(self);
}

Applet InitializeApplet(const int WIDTH, const int HEIGHT, const char* WINDOW_TITLE, int RESIZEABLE, int VSYNC)
{
    #ifndef MUZZLE_RETAIN_LEGACY
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        log_status(STATUS_WARNING, "Using Modern Pipeline");
    #endif

    glfwSetErrorCallback(muzzle_error);
    // Initialize GLFW
    if(!glfwInit()) 
        log_status(STATUS_FATAL_ERROR,"GLFW3 Could not Initialize, POINT OF FAILURE:\n\tMuzzle.Applet.InitializeApplet.glfwInit()");
    else 
        log_status(STATUS_SUCCESS, "GLFW3 Initialized Successfully");

    if (!VSYNC) log_status(STATUS_WARNING, "VSync was not enabled. This Muzzle Application will now use as much resources as it can take, this can cause high CPU/GPU Usage");

    // creating a sepreate applet struct, could just return the values. but, dont want to so i dont have to create a GLFWwindow *buffer
    Applet buf;
    buf.height = (int)(HEIGHT);
    buf.width = (int)(WIDTH);
    buf.window_title = (char*)(WINDOW_TITLE);
    buf.window_handle = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_TITLE, NULL, NULL);

    if (!buf.window_handle)
    {
        glfwTerminate();
        log_status(STATUS_FATAL_ERROR, "GLFW3 Could not Create the Window, POINT OF FAILURE:\n\tMuzzle.Applet.InitializeApplet.glfwCreateWindow()");
    }
    else
        log_status(STATUS_SUCCESS, "Window Created Succesfully");

    

    //glfwSetWindowPos(buf.window_handle)
    glfwSetKeyCallback(buf.window_handle, callback_key);
    glfwSetErrorCallback(muzzle_error);
    glfwMakeContextCurrent(buf.window_handle);

    #ifndef MUZZLE_RETAIN_LEGACY
        if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress))) log_status(STATUS_FATAL_ERROR, "GLAD could not initialize, POINT OF FAILURE:\n\tMuzzle.Applet.InitializeApplet.gladLoadGLLoader()");
    #endif


    if (VSYNC == MUZZLE_TRUE)
    {
        log_status(STATUS_INFO, "Enabled VSync");
        glfwSwapInterval(1);
    } 
    else glfwSwapInterval(0);

    glfwSetWindowAttrib(buf.window_handle, GLFW_RESIZABLE, RESIZEABLE);

    glfwSetWindowPos(buf.window_handle, 230,230);

    // NOTE: MAYBE: Instead of doing glViewport width height. Maybe get the actual framebuffer size and pass throught that?
    glViewport(0,0, WIDTH, HEIGHT);
    
    // TODO: Check if we need to enable GL_DEPTH_TEST, https://learnopengl.com/Advanced-OpenGL/Depth-testing
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // quickly clear the screen with white

    glEnable(GL_BLEND); // for transperency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    #ifdef MUZZLE_RETAIN_LEGACY
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);
    
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    #endif
    
    // TODO: Create Batchers
    buf.rect_batchers.length = 1;
    buf.rect_batchers.batchers = MZ_CALLOC(1, sizeof(batcher));
    
    if (buf.rect_batchers.batchers == NULL)
        log_status(STATUS_FATAL_ERROR, "Failed to allocate memory for rectangle batcher");
    
    buf.rect_batchers.batchers[0] = create_batcher_rectangle(MZ_BATCHER_SIZE);
    buf.rect_batchers.top = &buf.rect_batchers.batchers[0];
    
    return buf;
}