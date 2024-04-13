#include "WindowContext.h"
#include <iostream>

#define Log(x) std::cout<<x<<std::endl

//swapInterval is number of screen updates to wait to call the next drawcall
WindowContext::WindowContext(std::string title,float width,float height,int swapInterval)
    :m_title(title),m_width(width),m_height(height), m_swapInterval(swapInterval),m_window(nullptr)
{

}

WindowContext::~WindowContext()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

int WindowContext::init()
{
    if (!glfwInit())
    {
        Log("glfwInit error");
        return -1;
    }
        

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
    if (!m_window)
    {
        Log("glfwCreateWindow error");
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);// number of screen updates to wait to call the next drawcall
    GLenum status = glewInit();
    if (status != GLEW_OK)
    {
        Log("glew error");
        return -1;
    }

    return 1;
}