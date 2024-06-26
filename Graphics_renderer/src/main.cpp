#include <iostream>
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "GLDebugUtils.h"
#include "Utils.h"
#include "WindowContext.h"

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "ShortCuts.h"

#include "TestMenu.h"
#include "TestClearColor.h"
#include "TestGeometry.h"
#include "TestScene.h"
#include "GeometryType.h"
#include "Transform.h"
#include "Esthetics.h"

#define Enable  1;
#define Log(x) std::cout << x << std::endl;
#define imagePath0 "resources/images/white.png" // default texture image
#define imagePath1 "resources/images/kaguya.png"
#define imagePath2 "resources/images/grey_girl.png"


#define window_Width 640.0f
#define window_height 640.0f
#define nearPlane_z -320.0f
#define farPlane_z 320.0f

//TODO:: fix the multiple objects texture update -> set default texture


#if Enable == 1
int main(void)
{

    WindowContext _windowContext("Kaguya", window_Width, window_height, 1);
    if (_windowContext.init() == -1)
    {
        ASSERT(false);
    }
    GLFWwindow* window = _windowContext.m_window;

    glCall(glEnable(GL_BLEND));
    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


    glm::vec4 global_clear_color(0.3f, 0.7f, 0.6f, 1.0f);
    //glm::vec4 global_clear_color(1,0,0, 1.0f);
    Renderer renderer(global_clear_color);

    ImGui_ShortCut::ImGui_init(window);


    RenderContext geometryRenderContext(window_Width, window_height, nearPlane_z, farPlane_z);

    test::TestScene testScene;
    test::TestGeometry geometry1 = testScene.AddGeometry("ojbect1", GeometryType::QUAD, geometryRenderContext);
    test::TestGeometry geometry2 = testScene.AddGeometry("ojbect2", GeometryType::QUAD, geometryRenderContext);
    test::TestGeometry geometry3 = testScene.AddGeometry("ojbect3", GeometryType::QUAD, geometryRenderContext);
    
    test::TestGeometry geometry4 = testScene.AddGeometry("ojbect4", GeometryType::ELLIPSE, geometryRenderContext);


    float tintIntensity = 0.3f;

    

    geometry1
        .setGeometryType(GeometryType::QUAD)
        .setColor(Color::get(_Color::GOLD))
        .setDimensions_inUnits(2, 2)
        .setTexture(imagePath2, tintIntensity)
        .setPivot(glm::vec3(0, 200, 0))
        .setTranslation(glm::vec3(0, 200.0f, 0));

    geometry2
        .setGeometryType(GeometryType::ELLIPSE)
        .setColor(Color::get(_Color::OLIVE))
        .setDimensions_inUnits(2.1, 2.1)
        .setTexture(imagePath2)
        .setPivot(glm::vec3(120, 0, 0))
        .setTranslation(glm::vec3(0, 0, 0));



    geometry3
        .setGeometryType(GeometryType::QUAD)
        .setColor(Color::get(_Color::INDIGO))
        .setDimensions_inPixels(200, 200, 50)
        .setPivot(glm::vec3(120, 0, 0))
        .setTranslation(glm::vec3(-100.0f, -100.0f, 0));
    
    geometry4
        .setGeometryType(GeometryType::ELLIPSE)
        .setColor(Color::get(_Color::LIME))
        .setDimensions_inPixels(10, 10, 0)
        .setPivot(glm::vec3(0, 0, 0))
        .setTranslation(glm::vec3(120, 0, 0));



    float angle = 0;
    float step = 0;
    while (!glfwWindowShouldClose(window))
    {
        renderer.clear();
        ImGui_ShortCut::ImGui_NewFrame_Begin();


        geometry1.setRotation(glm::vec3(angle, 0, 0)).OnRender();

        geometry2.setRotation(glm::vec3(0, 0, angle)).OnRender();

        geometry3.setRotation(glm::vec3(0, 0, angle)).OnRender();

        geometry4.OnRender();


        angle += 1;
        step += 1;
        if (step > 400)
        {
            step = 0;
        }
        ImGui_ShortCut::ImGui_Frame_End();
        glCall(glfwSwapBuffers(window));
        glCall(glfwPollEvents());
    }

    ImGui_ShortCut::ImGui_Clean();


    return 0;
}
#endif









//
//
//
//
//int main(void)
//{
//    GLFWwindow* window;
//
//    /* Initialize the library */
//if (!glfwInit())
//return -1;
//
//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//
///* Create a windowed mode window and its OpenGL context */
//window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Hello World", NULL, NULL);
//if (!window)
//{
//    glfwTerminate();
//    return -1;
//}
//
///* Make the window's context current */
//glfwMakeContextCurrent(window);
//
//GLenum err = glewInit();
//if (GLEW_OK != err)
//{
//    Log("glew initialization failed !")
//}
//Log("Status: Using GLEW :" << glewGetString(GLEW_VERSION));
//// number of screen updates to wait to call the next drawcall
//glfwSwapInterval(1);
//
//glCall(glEnable(GL_BLEND));
//glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//
//
//
//float verteces[] =
//{
//    -50 , -50  , 0 , 0, // 0
//    -50 , 50, 0 , 1, // 1
//     50 , -50  , 1 , 0, // 2
//     50 , 50, 1 , 1 // 3
//};
//
//unsigned int indeces[]{
//       0 , 1 , 2, // first triangle
//       2 , 3 , 1 // second triagnle
//};
//
//
//VertexArray vao;
//
//VertexBuffer vbo(verteces, sizeof(verteces));
//
//VertexArrayLayout layout;
//layout.addAttribute<float>("position", 2);
//layout.addAttribute<float>("texture", 2);
//vao.addBuffer(vbo, layout);
//
//IndexBuffer ibo(indeces,
//    sizeof(indeces) / sizeof(indeces[0])
//);
//
//unsigned int texSlot = 0;
//Texture texture(imageFilePath, texSlot);
//
//std::string path = "resources/shader/shader.shader";
//Shader shader(path);
//shader.setUniform4f("u_color", 0.9f, 0.7f, 0.2f, 1);
//shader.setUniform1i("u_Texture", texSlot);
//
//
//glm::mat4 identity = glm::mat4(1.0f);
//glm::mat4 mvp;
//
//
//glm::mat4 proj = glm::ortho(-ScreenWidth / 2,
//    ScreenWidth / 2,
//    -ScreenHeight / 2,
//    ScreenHeight / 2,
//    nearPlane,
//    farPlane);
//
//
//glm::vec3 camera_translation(0.0f, 0.0f, 0.0f);
//glm::mat4 view = glm::translate(identity, camera_translation);
//
//glm::vec3 geometry_translation(0.0f, 0.0f, 0.0f);
//glm::mat4 model = glm::translate(identity, geometry_translation);
//
//
//
//mvp = proj * view * model;
//shader.setUniformMat4("u_MVP", mvp);
//
//Renderer renderer;
//
//
//ImGui::CreateContext();
//ImGuiIO& io = ImGui::GetIO(); (void)io;
//
//ImGui::StyleColorsDark();
//ImGui_ImplGlfw_InitForOpenGL(window, true);
//ImGui_ImplOpenGL3_Init();
//
//
//test::TestMenu testMenu;
//
//testMenu.AddTest<test::TestClearColor>("testClearColor");
//testMenu.AddTest<test::TestClearColor>("testClearColor 2");
//
//
//
//test::Test* currentTest = testMenu.m_currentTest;
//
///* Loop until the user closes the window */
//while (!glfwWindowShouldClose(window))
//{
//    // renderer.clear();
//
//
//    ImGui_ImplOpenGL3_NewFrame();
//    ImGui_ImplGlfw_NewFrame();
//    ImGui::NewFrame();
//
//    //glm::mat4 model = glm::translate(identity, geometry_translation);
//    //mvp = proj * view * model;
//    //shader.setUniformMat4("u_MVP", mvp);
//
//    currentTest = testMenu.m_currentTest;
//
//
//    if (currentTest == nullptr)
//    {
//        testMenu.OnGuiRender();
//        testMenu.OnRender();
//    }
//    else
//    {
//        if (ImGui::Button("<-"))
//        {
//            delete testMenu.m_currentTest;
//            testMenu.m_currentTest = nullptr;
//            currentTest = nullptr;
//        }
//
//        if (currentTest != nullptr)
//        {
//            currentTest->OnGuiRender();
//            currentTest->OnRender();
//        }
//
//    }
//
//
//
//
//
//    //ImGui::Begin("bg color");                          
//    //ImGui::Text("background color");
//    //ImGui::ColorEdit3("clear color", (float*)&renderer.m_ClearColor);
//    //ImGui::SliderFloat3("geometry translation", &geometry_translation.x, -ScreenWidth/2, ScreenWidth / 2);
//    //ImGui::End();
//
//
//   // renderer.draw(vao, ibo, shader);
//
//
//
//
//
//
//
//    ImGui::Render();
//    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//
//
//    /* Swap front and back buffers */
//    glCall(glfwSwapBuffers(window));
//
//    /* Poll for and process events */
//    glCall(glfwPollEvents());
//}
//
//
//// Cleanup
//ImGui_ImplOpenGL3_Shutdown();
//ImGui_ImplGlfw_Shutdown();
//ImGui::DestroyContext();
//
//glfwDestroyWindow(window);
//
//glfwTerminate();
//return 0;
//}

