#include "TestScene.h"

namespace test
{
	TestScene::TestScene()
	{

	}
	TestScene::~TestScene()
	{

	}

	void TestScene::OnUpdate()
	{

	}

	void TestScene::OnRender()
	{

	}

	void TestScene::OnGuiRender()
	{

	}

	test::TestGeometry TestScene::AddGeometry(std::string name, GeometryType type,RenderContext renderContext)
	{
		test::TestGeometry testGeo(renderContext);
		return testGeo;
	}

}