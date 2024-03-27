#pragma once

#include "Test.h"

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

		void SpawnGeometry();
		void SetTexture();
		void SetColor();
		void SetGeometryShape();

	};

}