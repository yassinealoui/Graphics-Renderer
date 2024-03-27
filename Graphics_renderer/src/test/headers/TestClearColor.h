#pragma once

#include "Test.h"
#include "glm/ext/vector_float4.hpp"

namespace test
{
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate() override;
		void OnRender() override ;
		void OnGuiRender() override;

		void setClearColor(glm::vec4 clearColor);
		void clear() const;

	protected:
		glm::vec4 m_ClearColor;

	};

}