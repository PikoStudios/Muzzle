#include "core/Applet.h"


void StartApplet(Applet *self)
{
    OnAppletUpdate(self);
}

Applet InitializeApplet(const int WIDTH, const int HEIGHT, const int TARGET_FPS, const char* WINDOW_TITLE)
{
    glfwSetErrorCallback(muzzle_error);
    // Initialize GLFW
    if(!glfwInit()) 
        log_status(FATAL_ERROR,"GLFW3 Could not Initialize, POINT OF FAILURE:\n\tMuzzle.Applet.InitializeApplet.glfwInit()");
    else 
        log_status(SUCCESS, "GLFW3 Initialized Successfully");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined(__APPLE__)
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
#endif

    // creating a sepreate applet struct, could just return the values. but, dont want to so i dont have to create a GLFWwindow *buffer
    Applet buf;
    buf.height = (int)(HEIGHT);
    buf.width = (int)(WIDTH);
    buf.WindowTitle = (char*)(WINDOW_TITLE);
    buf.targetFPS = (int)(TARGET_FPS);
    buf.window_handle = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_TITLE, NULL, NULL);

    if (!buf.window_handle)
    {
        glfwTerminate();
        log_status(FATAL_ERROR, "GLFW3 Could not Create the Window, POINT OF FAILURE:\n\tMuzzle.Applet.InitializeApplet.glfwCreateWindow()");
    }
    else
        log_status(SUCCESS, "Window Created Succesfully");

    //glfwSetWindowPos(buf.window_handle)
    glfwSetKeyCallback(buf.window_handle, callback_key);
    glfwMakeContextCurrent(buf.window_handle);
    glfwSwapInterval(0);

    rlLoadExtensions(glfwGetProcAddress);
    rlglInit(WIDTH, HEIGHT);

    rlViewport(0,0, WIDTH, HEIGHT);
    rlLoadIdentity();
    return buf;
}

