#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "../headers/VertexBuffer.h"
#include "../headers/VertexArray.h"
#include "../headers/IndexBuffer.h"
#include "../headers/GLDebugUtils.h"
#include "../headers/Shader.h"

#define Enable  1;
#define Log(x) std::cout << x << std::endl;

/*TEST*/
// TEST 1 : try to execute glVertexAttribPointer without binding the vbo , just bind the vao
//TODO : replace the unsigned int with uint32_t (more modern and clear)(c++11) include cstdint [decided based on compatibility]
//TODO : invert the place of priavte and public in your code so that the people reads the public first 
//TODO : use glDebugMessageCallBack() / glEnable(GL_DEBUG_OUTPUT) / glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS) instead of glCall
#if Enable == 1
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

       
    VertexArray vao;

    VertexBuffer vbo(verteces,sizeof(verteces));
 
    VertexArrayLayout layout;
    layout.addAttribute<float>("position", 2);
    vao.applyLayout(vbo, layout);


    IndexBuffer ibo(indeces,
        sizeof(indeces)/sizeof(indeces[0])
    );

    std::string path = "resources/shader/shader.shader";
    Shader shader(path);



    shader.UnBind();
    vao.UnBind();
    vbo.UnBind();
    ibo.UnBind();

    vao.Bind();
    vbo.Bind();
    ibo.Bind();
    shader.Bind();


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
#endif