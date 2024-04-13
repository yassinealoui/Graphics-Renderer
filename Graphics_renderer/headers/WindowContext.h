#pragma once
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include <string>
class WindowContext
{
public:
	GLFWwindow* m_window;
public:
	WindowContext(std::string title, float width, float height, int swapInterval);
	~WindowContext();
	int init();


private:
	float m_width,m_height;
	int m_swapInterval;
	std::string m_title;
};