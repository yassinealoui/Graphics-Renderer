#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "../headers/VertexBuffer.h"

#define log(x) std::cout << x << std::endl;


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480,480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
       log("glew initialization failed !")
    }
    log("Status: Using GLEW :" << glewGetString(GLEW_VERSION));

    float verteces[] =
    {
        -0.5 , 0  , // 0
        -0.5 , 0.5, // 1
         0.5 , 0  , // 2
         0.5 , 0.5  // 3
    };

    unsigned int indeces[]{
           0 , 1 , 2, // first triangle
           2 , 3 , 1 // second triagnle
    };
       
    
    VertexBuffer vbo(verteces,sizeof(verteces));





    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}