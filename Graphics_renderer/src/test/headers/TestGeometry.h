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
		TestGeometry(const RenderContext& renderContext);
		TestGeometry(float width, float height, float depth, GeometryType type, RenderContext renderContext);
		~TestGeometry();

		void OnUpdate() override;
		void OnRender() override;
		void OnGuiRender() override;



		std::shared_ptr<Transform> getTransform() const { return m_Transform; };
		TestGeometry& setTransform(Transform transform) { *m_Transform = transform; return *this; };


		std::shared_ptr <Texture> getTexture() const { return m_Texture; };
		TestGeometry& setTexture(Texture texture, float tintIntensity = 1.0)
		{
			m_TintIntensity = tintIntensity;
			*m_Texture = texture;

			return *this;
		};

		GeometryType getGeometryType() const { return m_type; };
		TestGeometry& setGeometryType(GeometryType type) { m_type = type;return *this; };


		TestGeometry& setColor(glm::vec4 color);


		TestGeometry& setDimensions_inPixels(float width, float height, float depth = 0);
		TestGeometry& setDimensions_inUnits(float width, float height , float depth = 0);

		TestGeometry& setTexture(std::string imagePath, float tintIntensity = 1.0, GLint texture_filter_param = GL_LINEAR);

		TestGeometry& set_Is_rotating_around_center_of_geometry(bool ans) {
			m_Is_rotating_around_center_of_geometry = ans;
		}

		bool get_Is_rotating_around_center_of_geometry() const
		{
			return m_Is_rotating_around_center_of_geometry;
		}

		glm::vec3 getPivot() const { return m_Pivot; };
		TestGeometry& setPivot(glm::vec3 pivot) { m_Pivot = pivot; return *this; }


		//higher abstraction for chaining setters
		TestGeometry& setTranslation(const glm::vec3& translation)
		{ 
			getTransform()->setTranslation(translation);
			return *this;
		};
		TestGeometry& setRotation(const glm::vec3& rotation)
		{ 
			getTransform()->setRotation(rotation);
			return *this;
		};
		TestGeometry& setScale(const glm::vec3& scale)
		{ 
			getTransform()->setScale(scale);
			return *this;
		};


	public:
		int pixels_per_unit;



	private:
		//memory potential memory leakage (float*) consider deleting it 
		float* getVerteces(int& length, float width, float height, float depth);
		//make verteces a memeber variable
		unsigned int* getIndeces(int& indeces_count, float* verteces);
		void updateShader();
		void updateRotationMatrix();
		void updateVertecesAndIndeces();
		void updateMVPmatrix();
		void updatePivotPtProjMatrix();
	private:
		glm::vec3 m_Pivot;
		bool m_Is_rotating_around_center_of_geometry;
		RenderContext m_RenderContext;
		GeometryType m_type;
		std::shared_ptr < Texture> m_Texture;
		glm::vec4 m_Color;
		float m_TintIntensity;
		Dimensions m_Dimensions;
		std::shared_ptr<Transform> m_Transform;
		std::shared_ptr <Shader> m_Shader;
		std::shared_ptr <VertexArray> m_VAO;
		std::shared_ptr <VertexBuffer> m_VBO;
		std::shared_ptr <IndexBuffer> m_IBO;
		std::shared_ptr <VertexArrayLayout> m_Layout;
	};
}

