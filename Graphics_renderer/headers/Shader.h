#pragma once
#include <string>


enum ShaderType
{
	VERTEX,
	FRAGMENT,
	NONE
};



class Shader
{
private:
	unsigned int m_renderID;

public:
	Shader(const std::string& path);
	~Shader();

	void Bind();
	void UnBind();
	static void setShadersources(const std::string& path, std::string& vertexShader, std::string& fragementShader) ;
	unsigned int CompileShader(ShaderType type, const std::string& source);
};