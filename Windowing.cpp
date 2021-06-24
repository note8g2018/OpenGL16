#include "Windowing.h"

Windowing::Windowing(int& width_window, int& height_window,
    string& title_window)
    : width_window(width_window), height_window(height_window),
    title_window(title_window)
{
}

Windowing::~Windowing()
{ 
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* Windowing::run()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    if(!glfwInit())
    {
        cout << "Failed to Init GLFW" << endl;
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfw window creation
    // --------------------
    window = glfwCreateWindow(width_window, height_window,
        title_window.c_str(), NULL, NULL);
    if(window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if(!gladLoadGL(glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
    }
    /*if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
    }*/
    cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
    set_callBack_functions();

    return window;
}

void Windowing::set_callBack_functions()
{
    glfwSetFramebufferSizeCallback(window,
        framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetKeyCallback(window, key_callback);    
}

void Windowing::processInput()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

