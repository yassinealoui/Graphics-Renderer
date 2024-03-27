#pragma once

#include "Test.h"
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>

namespace test
{
	class TestMenu : public Test
	{
	public:
		TestMenu();
		~TestMenu();


		void OnUpdate() override;
		void OnRender() override;
		void OnGuiRender() override;

		template<typename T>
		void AddTest(std::string testName)
		{
			m_Tests.push_back(std::make_pair(testName, []()->T*{return new T();}));
		};

		void clean();

	public:
		Test* m_currentTest;

	private:
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
		
	};
}
