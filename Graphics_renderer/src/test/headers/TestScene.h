#pragma once

#include "Test.h"
#include "GeometryType.h"
#include "TestGeometry.h"
#include "RenderContext.h"

namespace test
{
	class TestScene : public Test
	{
	public:
		TestScene();
		~TestScene();

		void OnUpdate() override;
		void OnRender() override;
		void OnGuiRender() override;

		test::TestGeometry AddGeometry(std::string name, GeometryType type, RenderContext renderContext);

	public:
		int pixels_per_unit = 100;

	private:
		std::unordered_map<std::string, test::TestGeometry> geometries;
	};

}