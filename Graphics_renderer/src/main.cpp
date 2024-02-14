#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "../headers/VertexBuffer.h"
#include "../headers/VertexArray.h"
#include "../headers/IndexBuffer.h"
#include "../headers/GLDebugUtils.h"
#include "../headers/Shader.h"


#define Log(x) std::cout << x << std::endl;

/*TEST*/
// TEST 1 : try to execute glVertexAttribPointer without binding the vbo , just bind the vao



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


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
       Log("glew initialization failed !")
    }
    Log("Status: Using GLEW :" << glewGetString(GLEW_VERSION));

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
       
    
    VertexBuffer vbo(verteces);
   
    VertexArray vao;
    vao.Bind();
    unsigned int attrib_index = vao.m_layout.addAttribute<float>(2);
    vao.m_layout.enableAttribute(attrib_index);

    IndexBuffer ibo(indeces,
        sizeof(indeces)/sizeof(indeces[0])
    );

    std::string path = "resources/shader/shader.txt";
    Shader shader(path);





    vao.Bind();
    vbo.Bind();
    ibo.Bind();


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glCall(glClear(GL_COLOR_BUFFER_BIT));


        glCall(glDrawArrays(GL_TRIANGLES, 0, ibo.getCount()));


        /* Swap front and back buffers */
        glCall(glfwSwapBuffers(window));

        /* Poll for and process events */
        glCall(glfwPollEvents());
    }

    glfwTerminate();
    return 0;
}