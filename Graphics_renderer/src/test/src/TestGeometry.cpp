#include "TestGeometry.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"
#include <cmath>
#include <iostream>
#include "Utils.h"
//TODO:: store the verteces to avoid redundant calculation
// TODO: impliment rotation around a vector not just x , y , z axis
// TODO: switch to units system not pixels
// the values of cos and sin are not 100% accurate test it with 90° in rad

#define BASIC_SHADER "resources/shader/shader.shader"
#define CIRCLE_SHADER "resources/shader/circle.shader"


#define whiteImage "resources/images/white.png" 


namespace test
{

	TestGeometry::TestGeometry(float width, float height, float depth,GeometryType type,RenderContext renderContext) 
		:m_Dimensions(width,height,depth),m_type(type),m_RenderContext(renderContext),m_TintIntensity(1.0)
	{
		/*m_Color = glm::vec4(
			renderContext.m_ClearColor[0],
			renderContext.m_ClearColor[1],
			renderContext.m_ClearColor[2],
			renderContext.m_ClearColor[3]
		);*/

		int verteces_count;
		float* verteces = getVerteces(verteces_count,m_Dimensions.m_Width, m_Dimensions.m_Height, m_Dimensions.m_Depth);
		int indeces_count;
		unsigned int* indeces = getIndeces(indeces_count,verteces);

		m_VAO = std::make_shared<VertexArray>();
		m_VBO = std::make_shared<VertexBuffer>(verteces, sizeof(verteces)*verteces_count);
		m_Layout = std::make_shared<VertexArrayLayout>();

		m_Layout->addAttribute<float>("position", 3);
		m_Layout->addAttribute<float>("texture", 2);
		m_VAO->addBuffer(*m_VBO, *m_Layout);

		m_IBO = std::make_shared<IndexBuffer>(indeces, indeces_count);

		m_Shader = std::make_shared<Shader>(BASIC_SHADER);
		m_Shader->setUniform4f("u_color", m_Color.r, m_Color.g, m_Color.b, m_Color.a);
		setTexture(whiteImage, 1.0f,GL_NEAREST);

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
		float* verteces;
		
		switch (m_type)
		{
		case GeometryType::ELLIPSE://just return a Quad and the shader will create the circle
			length = 20; // don't forget to update this when changing the Verteces !!!
			return verteces = new float[] {
				-width / 2, -height / 2, 0, 0, 0,   // 0
					-width / 2, height / 2, 0, 0, 1,  // 1
					width / 2, -height / 2, 0, 1, 0, // 2
					width / 2, height / 2, 0, 1, 1, // 3

			};
		case GeometryType::TRIANGLE:
			length = 15; // don't forget to update this when changing the Verteces !!!
			return verteces = new float[] {
				-width / 2, -height / 2, 0, 0, 0,   // 0
					0, height / 2, 0, 0, 1,  // 1
					width / 2, -height / 2, 0, 1, 0, // 2
			};
		default://default is a Quad
			length = 20; // don't forget to update this when changing the Verteces !!!
			return verteces = new float[] {
				-width / 2, -height / 2, 0, 0, 0,   // 0
					-width / 2, height / 2, 0, 0, 1,  // 1
					width / 2, -height / 2, 0, 1, 0, // 2
					width / 2, height / 2, 0, 1, 1, // 3

			};
		}



		return verteces;
	};

	unsigned int* TestGeometry::getIndeces(int& indeces_count,float* verteces)
	{
		unsigned int* indeces;
		switch (m_type)
		{
		case GeometryType::TRIANGLE:
			indeces_count = 3; // don't forget to update this when changing the indeces !!!
			return 		new unsigned int[] {
				0, 1, 2, // front side triangle
			};
		default://default is a Quad
			indeces_count = 6; // don't forget to update this when changing the indeces !!!
			return 		new unsigned int[]{
			   0 , 1 , 2, // front side first triangle
			   2 , 3 , 1,// front side second triagnle
			};
		}


		return indeces;
	}


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

	//texture slot is 0 by default
	void TestGeometry::setTexture(std::string imagePath, float tintIntensity , GLint texture_filter_param )
	{
		m_TintIntensity = tintIntensity;
		unsigned int texSlot = 0;
		m_Texture = std::make_shared<Texture>(imagePath, texSlot, texture_filter_param);
		m_Shader->setUniform1i("u_Texture", texSlot);
	}










	bool once = true;
	//clean on render (globalize proj..etc)
	void TestGeometry::OnRender()
	{
		const double pi = 3.141592653589793238462643383279502884L;

		float z_angle_rad = m_Transform->getRotation().z * (pi / 180);
		float x_angle_rad = m_Transform->getRotation().x * (pi / 180);
		float y_angle_rad = m_Transform->getRotation().y * (pi / 180);	
		
		int length;
		float* verteces = getVerteces(length, m_Dimensions.m_Width, m_Dimensions.m_Height, m_Dimensions.m_Depth);
		int indeces_count;
		unsigned int* indeces = getIndeces(indeces_count, verteces);
		m_IBO = std::make_shared<IndexBuffer>(indeces, indeces_count);


		//get this section out of OnRender
		if (m_type == GeometryType::ELLIPSE)
		{
			m_Shader = std::make_shared<Shader>(CIRCLE_SHADER);
		}
		else {
			m_Shader = std::make_shared<Shader>(BASIC_SHADER);
		}
		m_Shader->setUniform4f("u_color", m_Color.r, m_Color.g, m_Color.b, m_Color.a);
		

		glm::mat4 rotation_around_x_axis = glm::mat4(
			1.0f, 0.0f, 0.0f, 0.0f, 
			0.0f, cos(x_angle_rad),-sin(x_angle_rad), 0.0f,
			0.0f, sin(x_angle_rad), cos(x_angle_rad), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f  
		);

		glm::mat4 rotation_around_y_axis = glm::mat4(
			cos(y_angle_rad), 0.0f, -sin(y_angle_rad), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sin(y_angle_rad),0.0f, cos(y_angle_rad), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		glm::mat4 rotation_around_z_axis = glm::mat4(
			cos(z_angle_rad), -sin(z_angle_rad), 0.0f, 0.0f,
			sin(z_angle_rad), cos(z_angle_rad), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		glm::mat4 rotation_around_xyz = rotation_around_x_axis * rotation_around_y_axis * rotation_around_z_axis;

		m_Shader->setUniformMat4("u_Rotation", rotation_around_xyz);

		m_VBO = std::make_shared<VertexBuffer>(verteces, sizeof(verteces) * length);
		





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


		m_Shader->setUniform1f("u_TintIntensity", m_TintIntensity);

		m_Texture->Bind();
		Renderer renderer(glm::vec4(0));
		renderer.draw(*m_Layout,*m_VBO,*m_VAO, *m_IBO, *m_Shader);
	};


	void TestGeometry::OnGuiRender()
	{

	};

	void TestGeometry::setColor(glm::vec4 color)
	{
		m_Color = color;
		m_Shader->setUniform4f("u_color", color.r, color.g, color.b, color.a);
	}

}













//
//verteces = new float[] {
//	-width / 2, -height / 2, 0, 0, 0,   // 0
//		-width / 2, height / 2, 0, 0, 1,  // 1
//		width / 2, -height / 2, 0, 1, 0, // 2
//		width / 2, height / 2, 0, 1, 1, // 3
//
//	   //-width / 2, -height / 2, -depth, 0, 0,   // 4
//	   //-width / 2,  height / 2, -depth, 0, 1,  // 5
//	   // width / 2, -height / 2, -depth, 1, 0, // 6
//	   // width / 2,  height / 2, -depth, 1, 1 // 7
//};

//unsigned int indeces[]{
//	   0 , 1 , 2, // front side first triangle
//	   2 , 3 , 1,// front side second triagnle
//
//	   //2 , 3 , 6, // right side first triangle
//	   //6 , 7 , 3,// right side second triagnle
//
//	   //0 , 1 , 4, // left side first triangle
//	   //4 , 5 , 1,// left side second triagnle
//
//	   //1 , 5 , 3, // top side first triangle
//	   //3 , 7 , 5,// top side second triagnle
//
//	   //4 , 0 , 6, // bottom side first triangle
//	   //6 , 2 , 0,// bottom side second triagnle
//
//	   //4 , 5 , 6, // back side first triangle
//	   //6 , 7 , 5// back side second triagnle
//};





