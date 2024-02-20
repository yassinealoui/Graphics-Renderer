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

	void Bind() const;
	void UnBind() const;
	static void setShadersources(const std::string& path, std::string& vertexShader, std::string& fragementShader);
	unsigned int CompileShader(ShaderType type, const std::string& source);

	void setUniform4f(const std::string& u_name, float v0, float v1, float v2, float v3) const;
	void setUniform_random_4f(const std::string& u_name) const;
};