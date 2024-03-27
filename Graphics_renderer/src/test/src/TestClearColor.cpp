#include "TestClearColor.h"
#include <GLEW/glew.h>
#include <GLDebugUtils.h>
#include "imgui/imgui.h"

namespace test {
	TestClearColor::TestClearColor() :m_ClearColor(glm::vec4(0.4f, 0.6f, 0.8f, 1.0f))
	{

	}

	TestClearColor::~TestClearColor()
	{

	}


	void TestClearColor::OnUpdate()
	{

	}

	void TestClearColor::OnRender()
	{
		clear();

	}

	void TestClearColor::OnGuiRender()
	{
		ImGui::ColorEdit3("clear color", (float*)&m_ClearColor);
	}

	void TestClearColor::setClearColor(glm::vec4 clearColor)
	{
		m_ClearColor = clearColor;
	}

	void TestClearColor::clear() const
	{
		glCall(glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a));
		glCall(glClear(GL_COLOR_BUFFER_BIT));
	}
}
