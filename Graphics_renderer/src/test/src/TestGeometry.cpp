#include "TestGeometry.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"

namespace test
{

	TestGeometry::TestGeometry(RenderContext renderContext):m_RenderContext(renderContext)
	{

		float verteces[] =
		{
		    -50 , -50  , 0 , 0,   // 0
		    -50 ,  50  , 0 , 1,  // 1
		     50 , -50  , 1 , 0, // 2
		     50 ,  50  , 1 , 1 // 3
		};

		
		unsigned int indeces[]{
		       0 , 1 , 2, // first triangle
		       2 , 3 , 1 // second triagnle
		};
		m_VAO = std::make_shared<VertexArray>();
		m_VBO = std::make_shared<VertexBuffer>(verteces, sizeof(verteces));
		m_Layout = std::make_shared<VertexArrayLayout>();

		m_Layout->addAttribute<float>("position", 2);
		m_Layout->addAttribute<float>("texture", 2);
		m_VAO->addBuffer(*m_VBO, *m_Layout);
		
		m_IBO = std::make_shared<IndexBuffer>(indeces, sizeof(indeces) / sizeof(indeces[0]));
		
		std::string path = "resources/shader/shader.shader";
		m_Shader = std::make_shared<Shader>(path);
		m_Shader->setUniform4f("u_color", 0.9f, 0.7f, 0.5f, 1);
		
		m_Transform = std::make_shared<Transform>();
		

		
		
		
		
		
	}
	TestGeometry::~TestGeometry()
	{
		
	}


	void TestGeometry::OnUpdate() 
	{

	};
	//test shared pointers

	//clean on render (globalize proj..etc)
	void TestGeometry::OnRender()
	{

		glm::mat4 proj = glm::ortho(
			-m_RenderContext.m_window_width / 2,
			m_RenderContext.m_window_width / 2,
			-m_RenderContext.m_window_height / 2,
			m_RenderContext.m_window_height / 2,
			m_RenderContext.m_nearPlane_z,
			m_RenderContext.m_farPlane_z);

		glm::mat4 identity = glm::mat4(1.0f);
		glm::mat4 mvp;

		glm::vec3 camera_translation(0.0f, 0.0f, 0.0f);
		glm::mat4 view = glm::translate(identity, camera_translation);

		
		glm::mat4 model = glm::translate(identity, m_Transform->getTranslation());
		mvp = proj * view * model;
		m_Shader->setUniformMat4("u_MVP", mvp);




		Renderer renderer;
		renderer.draw(*m_VAO, *m_IBO, *m_Shader);
	};


	void TestGeometry::OnGuiRender()
	{

	};

	void setColor()
	{

	}

}






















