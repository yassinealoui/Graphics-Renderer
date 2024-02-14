#pragma once
#include <string>

class Shader
{
private:
	unsigned int m_renderID;

public:
	Shader(const std::string& path);
	~Shader();

	void Bind();
	void UnBind();
	static void setShaders(const std::string& path, std::string& vertexShader, std::string& fragementShader) ;
};