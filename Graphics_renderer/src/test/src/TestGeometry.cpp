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

	TestGeometry::TestGeometry(float width, float height, float depth,RenderContext renderContext) 
		:m_Dimensions(width,height,depth),m_RenderContext(renderContext)
	{
		int verteces_count;
		float* verteces = getVerteces(verteces_count,m_Dimensions.m_Width, m_Dimensions.m_Height, m_Dimensions.m_Depth);

		std::cout << verteces_count<<" " << sizeof(verteces) << std::endl;;

		unsigned int indeces[]{
			   0 , 1 , 2, // front side first triangle
			   2 , 3 , 1,// front side second triagnle

			   2 , 3 , 6, // right side first triangle
			   6 , 7 , 3,// right side second triagnle

			   0 , 1 , 4, // left side first triangle
			   4 , 5 , 1,// left side second triagnle

			   1 , 5 , 3, // top side first triangle
			   3 , 7 , 5,// top side second triagnle

			   4 , 0 , 6, // bottom side first triangle
			   6 , 2 , 0,// bottom side second triagnle

			   4 , 5 , 6, // back side first triangle
			   6 , 7 , 5// back side second triagnle
		};
		m_VAO = std::make_shared<VertexArray>();
		m_VBO = std::make_shared<VertexBuffer>(verteces, sizeof(verteces)*verteces_count);
		m_Layout = std::make_shared<VertexArrayLayout>();

		m_Layout->addAttribute<float>("position", 3);
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

	float* TestGeometry::getVerteces(int& length,float width, float height , float depth)
	{
		length = 40; // don't forget to update this when changing the Verteces !!!
		
					 
		//float z = (m_RenderContext.m_nearPlane_z + m_RenderContext.m_farPlane_z) / 2;//random choice
		float* verteces = new float[] {
			    -width / 2, -height / 2, 0, 0, 0,   // 0
				-width / 2,  height / 2, 0, 0, 1,  // 1
				 width / 2, -height / 2, 0, 1, 0, // 2
				 width / 2,  height / 2, 0, 1, 1, // 3

				-width / 2, -height / 2, -depth, 0, 0,   // 4
				-width / 2,  height / 2, -depth, 0, 1,  // 5
				 width / 2, -height / 2, -depth, 1, 0, // 6
				 width / 2,  height / 2, -depth, 1, 1 // 7


		};
		return verteces;
	};


	void TestGeometry::setDimensions_inPixels(float width, float height, float depth)
	{
		m_Dimensions = Dimensions(width, height,depth);
		int length;
		float* verteces = getVerteces(length, m_Dimensions.m_Width, m_Dimensions.m_Height,m_Dimensions.m_Depth);
		m_VBO = std::make_shared<VertexBuffer>(verteces, sizeof(verteces) * length);
	};
	void TestGeometry::setDimensions_inUnits(float width, float height)
	{

	}

	bool once = true;
	//clean on render (globalize proj..etc)
	void TestGeometry::OnRender()
	{
		const double pi = 3.141592653589793238462643383279502884L;

		////rotate
		////get the rotation matrix
		float z_angle_rad = m_Transform->getRotation().z * (pi / 180);
		float x_angle_rad = m_Transform->getRotation().x * (pi / 180);
		float y_angle_rad = m_Transform->getRotation().y * (pi / 180);
		

		// the values of cos and sin are not 100% accurate test it with 90° in rad

		int length;
		float* verteces = getVerteces(length, m_Dimensions.m_Width, m_Dimensions.m_Height, m_Dimensions.m_Depth);

		if (once)
		{
			Log("old:");
			for (int i = 0; i < 16; ++i) {
				std::cout << verteces[i] << " ";
				if (i == 3 || i == 7 || i == 11)
					std::cout << std::endl;
			}
			
		}

		//around z axis rotation (change in the x y plane)
		for (int i = 0;i < length;i += 5)
		{
			float x_after_rotation = verteces[i] * cos(z_angle_rad) - verteces[i + 1] * sin(z_angle_rad);
			float y_after_rotation = verteces[i] * sin(z_angle_rad) + verteces[i + 1] * cos(z_angle_rad);

			verteces[i] = x_after_rotation;
			verteces[i + 1] = y_after_rotation;
		}

		// the object will rotate in correct way always , but if you put the nearplane and farplane
		// too close like -1px and 1px the verteces' new positions will be outside of the clip space 
		//so it will give an odd rotation

		//around x axis rotation(change in the y z plane)
		for (int i = 0;i < length;i += 5)
		{
			float y_after_rotation = verteces[i + 1] * cos(x_angle_rad) - verteces[i + 2] * sin(x_angle_rad);
			float z_after_rotation = verteces[i + 1] * sin(x_angle_rad) + verteces[i + 2] * cos(x_angle_rad);

			verteces[i + 1] = y_after_rotation;
			verteces[i + 2] = z_after_rotation;
		}


		//around y axis rotation(change in the x z plane)
		for (int i = 0;i < length;i += 5)
		{
			float x_after_rotation = verteces[i] * cos(y_angle_rad) - verteces[i + 2] * sin(y_angle_rad);
			float z_after_rotation = verteces[i] * sin(y_angle_rad) + verteces[i + 2] * cos(y_angle_rad);

			verteces[i] = x_after_rotation;
			verteces[i + 2] = z_after_rotation;
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






















