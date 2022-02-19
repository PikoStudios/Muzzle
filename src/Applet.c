#include "core/Applet.h"


void StartApplet(Applet *self)
{
    OnAppletUpdate(self);
}

Applet InitializeApplet(const int WIDTH, const int HEIGHT, const char* WINDOW_TITLE, int RESIZEABLE, int VSYNC)
{
#ifdef MUZZLE_USE_MODERN_RENDERER
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    printf("fuck");
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

    #ifdef MUZZLE_USE_MODERN_RENDERER
        rlLoadExtensions(glfwGetProcAddress);
        void* data = __internal_rlgl_get_data_structure();

        // NOTE: MAYBE: Create default white texture???

        rlLoadShaderDefault();
        data->State.currentShaderId = data->State.defaultShaderId;
        data->State.currentShaderLocs = data->State.defaultShaderLocs;
        
        data->defaultBranch = rlLoadRenderBatch(RL_DEFAULT_BATCH_BUFFERS, RL_DEFAULT_BATCH_BUFFER_ELEMENTS);
        data->currentBatch = &data->defaultBatch;

        for (int i = 0; i < RL_MAX_MATRIX_STACK_SIZE; i++)
        {
            data->State.stack[i] = rlMatrixIdentity();
        }

        data->State.transform = rlMatrixIdentity();
        data->State.projection = rlMatrixIdentity();
        data->State.modelview = rlMatrixIdentity();
        data->State.currentMatrix = &data->State.modelview;

        log_status(STATUS_SUCCESS, "Modern Renderer Initialized Successfully");
    #endif
    
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

    return buf;
}