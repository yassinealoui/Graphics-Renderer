#pragma once

#include "TestClearColor.h";

namespace test
{
	class TestGeometry : public TestClearColor
	{
	public:
		TestGeometry();
		~TestGeometry();

		virtual void onUpdate() {};
		virtual void onRender() {};
		virtual void onGuiRender() {};

	};
}