#pragma once

#include "TestClearColor.h";
#include "GeometryType.h"
#include "Texture.h"
#include "Transform.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "RenderContext.h"
#include "Shader.h"
#include <memory>

//try to use smart pointers
//try using const ref in parameters
struct Dimensions
{
	float m_Width;
	float m_Height;
	float m_Depth;

	Dimensions(float width, float height, float depth) :m_Width(width), m_Height(height), m_Depth(depth)
	{}
};



namespace test
{
	class TestGeometry : public Test
	{
	public:
		TestGeometry(float width, float height, float depth ,RenderContext renderContext);
		~TestGeometry();

		void OnUpdate() override;
		void OnRender() override;
		void OnGuiRender() override;


		std::shared_ptr<Transform> getTransform() const { return m_Transform; };
		void setTransform(Transform transform) { *m_Transform = transform; };


		Texture* getTexture() const { return m_Texture; };
		void setTexture(Texture* texture) { m_Texture = texture; };

		GeometryType getGeometryType() const { return m_type; };
		void setGeometryType(GeometryType type) { m_type = type; };


		void setColor(glm::vec4 color);


		void setDimensions_inPixels(float width, float height, float depth);
		void setDimensions_inUnits(float width, float height);

	public:
		int pixels_per_unit;



	private:
		//memory potential memory leakage (int*) consider deleting it 
		float* getVerteces(int& length,float width,float height, float depth);

	private:
		//if one those memebers doesn't change when updating them , just change them to pointer (shared_ptr)
		RenderContext m_RenderContext;
		GeometryType m_type;
		Texture* m_Texture;

		
		Dimensions m_Dimensions;
		std::shared_ptr<Transform> m_Transform;
		std::shared_ptr <Shader> m_Shader;
		std::shared_ptr <VertexArray> m_VAO;
		std::shared_ptr <VertexBuffer> m_VBO;
		std::shared_ptr <IndexBuffer> m_IBO;
		std::shared_ptr <VertexArrayLayout> m_Layout;
	};
}

