#include "core/Applet.h"


void StartApplet(Applet *self)
{
    OnAppletUpdate(self);
}

Applet InitializeApplet(const int WIDTH, const int HEIGHT, const char* WINDOW_TITLE, int RESIZEABLE, int VSYNC)
{
#ifdef MUZZLE_DANGEROUS_USE_MODERN_GRAPHICS_PIPELINE
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    __internal_create_mz_renderer();
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
    buf.WindowTitle = (char*)(WINDOW_TITLE);
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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // quickly clear the screen with white 

    glEnable(GL_BLEND); // for transperency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

#ifdef MUZZLE_DANGEROUS_USE_MODERN_GRAPHICS_PIPELINE
    gladLoadGL();
#endif

    return buf;
}

