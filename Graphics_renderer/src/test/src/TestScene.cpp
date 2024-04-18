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

	//add list of geometry to update their pixels_per_unit 
	test::TestGeometry TestScene::AddGeometry(std::string name, GeometryType type,RenderContext renderContext)
	{
		test::TestGeometry testGeo(100,100,100,renderContext);
		testGeo.pixels_per_unit = 100;
		return testGeo;
	}

}