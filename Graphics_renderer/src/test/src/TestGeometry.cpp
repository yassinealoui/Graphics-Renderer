#include "TestGeometry.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"
#include <cmath>
#include <iostream>
#include "Utils.h"
//TODO:: store the verteces to avoid redundant calculation
//TODO:: proper implimentation of the rotation

namespace test
{

	TestGeometry::TestGeometry(float width, float height, RenderContext renderContext) 
		:m_Dimensions(width,height),m_RenderContext(renderContext)
	{
		int verteces_count;
		float* verteces = getVerteces(verteces_count,m_Dimensions.m_Width, m_Dimensions.m_Height);

		std::cout << verteces_count<<" " << sizeof(verteces) << std::endl;;

		unsigned int indeces[]{
			   0 , 1 , 2, // first triangle
			   2 , 3 , 1 // second triagnle
		};
		m_VAO = std::make_shared<VertexArray>();
		m_VBO = std::make_shared<VertexBuffer>(verteces, sizeof(verteces)*verteces_count);
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

	float* TestGeometry::getVerteces(int& length,float width, float height)
	{
		float* verteces = new float[]{
			    -width / 2, -height / 2, 0, 0,   // 0
				-width / 2,  height / 2, 0, 1,  // 1
				 width / 2, -height / 2, 1, 0, // 2
				 width / 2,  height / 2, 1, 1 // 3
		};
		length = 16;
		return verteces;
	};


	void TestGeometry::setDimensions_inPixels(float width, float height)
	{
		m_Dimensions = Dimensions(width, height);
		int length;
		float* verteces = getVerteces(length, m_Dimensions.m_Width, m_Dimensions.m_Height);
		m_VBO = std::make_shared<VertexBuffer>(verteces, sizeof(verteces) * length);
	};


	bool once = true;
	//clean on render (globalize proj..etc)
	void TestGeometry::OnRender()
	{
		const double pi = 3.141592653589793238462643383279502884L;

		////rotate
		////get the rotation matrix
		float y_angle_rad = m_Transform->getRotation().y * (pi / 180);

		// the values of cos and sin are not 100% accurate test it with 90° in rad
		float cos_ = cos(y_angle_rad);
		float sing = sin(y_angle_rad);

		int length;
		float* verteces = getVerteces(length, m_Dimensions.m_Width, m_Dimensions.m_Height);
		if (once)
		{
			Log("old:");
			for (int i = 0; i < 16; ++i) {
				std::cout << verteces[i] << " ";
				if (i == 3 || i == 7 || i == 11)
					std::cout << std::endl;
			}
			
		}



		for (int i = 0;i < length;i += 4)
		{
			float x_after_rotation = verteces[i] * cos(y_angle_rad) - verteces[i + 1] * sin(y_angle_rad);
			float y_after_rotation = verteces[i] * sin(y_angle_rad) + verteces[i + 1] * cos(y_angle_rad);

			verteces[i] = x_after_rotation;
			verteces[i + 1] = y_after_rotation;
		}
		m_VBO = std::make_shared<VertexBuffer>(verteces, sizeof(verteces) * length);
		

		if (once)
		{
			Log("\n \n new:");
			for (int i = 0; i < 16; ++i) {
				std::cout << verteces[i] << " ";
				if (i == 3 || i == 7 || i == 11)
					std::cout << std::endl;
			}
			once = false;
		}



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
		renderer.draw(*m_Layout,*m_VBO,*m_VAO, *m_IBO, *m_Shader);
	};


	void TestGeometry::OnGuiRender()
	{

	};

	void TestGeometry::setColor(glm::vec4 color)
	{
		m_Shader->setUniform4f("u_color", color.r, color.g, color.b, color.a);
	}

}






















