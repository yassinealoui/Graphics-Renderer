#include "TestMenu.h"
#include <imgui/imgui.h>


namespace test
{
	TestMenu::TestMenu()
	{

	}

	TestMenu::~TestMenu()
	{
		
	}

	void TestMenu::clean()
	{
		delete m_currentTest;
		m_currentTest = nullptr;
	}

	void TestMenu::OnRender()
	{
	
	}

	void TestMenu::OnUpdate()
	{

	}

	void TestMenu::OnGuiRender()
	{
		for (auto test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str())) 
			{
				m_currentTest = test.second();
			}
		}	
	}
}




/*for (auto name_test_lambda_pair : m_tests)
		{
			auto test_cached = m_testsCache.find(name_test_lambda_pair.first);
			if (test_cached != m_testsCache.end()) {
				test_cached->second->OnGuiRender();
			}
			else {
				Test* temp_test = name_test_lambda_pair.second();
				m_testsCache[name_test_lambda_pair.first] = temp_test;
				temp_test->OnGuiRender();
			}
		}*/