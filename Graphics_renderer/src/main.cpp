#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "../headers/VertexBuffer.h"
#include "../headers/VertexArray.h"
#include "../headers/IndexBuffer.h"
#include "../headers/GLDebugUtils.h"
#include "../headers/Shader.h"
#include "../headers/Renderer.h"
#include "main.h"
#include "../headers/Texture.h"
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../headers/Utils.h"

#define Enable  1;
#define Log(x) std::cout << x << std::endl;
#define imageFilePath "resources/images/kaguya.png"

#define ScreenWidth 480.0f
#define ScreenHeight 480.0f
#define nearPlane -1.0f
#define farPlane 1.0f

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
    window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Hello World", NULL, NULL);
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
    // number of screen updates to wait to call the next drawcall
     glfwSwapInterval(10);
    float verteces[] =
    {
        -50 , 0  , 0 , 0, // 0
        -50 , 100, 0 , 1, // 1
         50 , 0  , 1 , 0, // 2
         50 , 100, 1 , 1 // 3
    };

    unsigned int indeces[]{
           0 , 1 , 2, // first triangle
           2 , 3 , 1 // second triagnle
    };

       
    VertexArray vao;

    VertexBuffer vbo(verteces,sizeof(verteces));
 
    VertexArrayLayout layout;
    layout.addAttribute<float>("position", 2);
    layout.addAttribute<float>("texture", 2);
    vao.addBuffer(vbo, layout);
   
    IndexBuffer ibo(indeces,
        sizeof(indeces) / sizeof(indeces[0])
    );

    unsigned int texSlot = 0;
    Texture texture(imageFilePath,texSlot);

    std::string path = "resources/shader/shader.shader";
    Shader shader(path);
    shader.setUniform4f("u_color", 0.9f, 0.7f, 0.2f, 1);
    shader.setUniform1i("u_Texture", texSlot);


    glm::mat4 identity = glm::mat4(1.0f);
    glm::mat4 mvp;


    glm::mat4 proj = glm::ortho(-ScreenWidth / 2, 
                                ScreenWidth / 2,
                                -ScreenHeight / 2, 
                                ScreenHeight / 2, 
                                nearPlane, 
                                farPlane);
    

    glm::vec3 camera_translation(-100.0f, -50.0f, 0.0f);
    glm::mat4 view = glm::translate(identity, camera_translation);

    glm::vec3 geometry_translation(300.0f, 80.0f, 0.0f);
    glm::mat4 model = glm::translate(identity, geometry_translation);



    mvp = proj * view * model;
    shader.setUniformMat4("u_MVP", mvp);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        //shader.setUniform_random_4f("u_color");
        Renderer::Draw(vao, ibo, shader);
       


        /* Swap front and back buffers */
        glCall(glfwSwapBuffers(window));

        /* Poll for and process events */
        glCall(glfwPollEvents());
    }

    glfwTerminate();
    return 0;
}
#endif