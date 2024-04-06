#pragma once

#include "TestClearColor.h";
#include "GeometryType.h"
#include "Texture.h"

//try to use smart pointers

namespace test
{
	class TestGeometry : public TestClearColor
	{
	public:
		TestGeometry();
		~TestGeometry();

		void OnUpdate() override;
		void OnRender() override;
		void OnGuiRender() override;


		Transform getTransform() const { return m_Transform; };
		void setTransform(Transform transform) { m_Transform = transform; };

		Texture* getTexture() const { return m_Texture; };
		void setTexture(Texture* texture) { m_Texture = texture;};
		
		GeometryType getGeometryType() const { return m_type;};
		void setGeometryType(GeometryType type);


		void setColor();
		

	private:
		GeometryType m_type;
		Transform m_Transform;
		Texture* m_Texture;
	};
}

