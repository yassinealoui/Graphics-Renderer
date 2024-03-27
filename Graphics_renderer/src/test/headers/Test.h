#pragma once

namespace test
{
	class Test
	{
	public:
		Test() {};
		~Test() {};

		virtual void OnUpdate() {};
		virtual void OnRender() {};
		virtual void OnGuiRender() {};
	};

}