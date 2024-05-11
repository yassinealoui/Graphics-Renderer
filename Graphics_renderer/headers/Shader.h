#pragma once
#include <string>
#include "glm/ext/matrix_float4x4.hpp"


//TODO: add a uniform caching system

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
	static void UnBind();
	static void setShadersources(const std::string& path, std::string& vertexShader, std::string& fragementShader);
	unsigned int CompileShader(ShaderType type, const std::string& source);

	void setUniform4f(const std::string& u_name, float v0, float v1, float v2, float v3) const;
	void setUniform1i(const std::string& u_name, unsigned int value) const;
	void setUniform1f(const std::string& u_name, float value) const;
	void setUniformMat4(const std::string& u_name, const glm::mat4& mat) const;
	void setUniform_random_4f(const std::string& u_name) const;
};