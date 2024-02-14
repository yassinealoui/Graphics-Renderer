#include "../headers/Shader.h"
#include "../headers/GLDebugUtils.h"
#include "glew.h"
#include "../headers/Utils.h"
#include <fstream>
#include "glew.h"

#define Log(x) std::cout << x << std::endl;

//path relative the project dir
Shader::Shader(const std::string& path)
{
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
	setShaders(path, vertexShaderSource, fragmentShaderSource);
	
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	const char* vss = vertexShaderSource.c_str();
	glShaderSource(vs, 1, &vss, nullptr);
	glCompileShader(vs);
	

	
	//compile
	//add to program
}

Shader::~Shader()
{
	glCall(glDeleteShader(m_renderID));
}

void Shader::Bind()
{
	glCall(glUseProgram(m_renderID));
}

void Shader::UnBind()
{
	glCall(glUseProgram(0));
}


enum ShaderType
{
	VERTEX,
	FRAGMENT,
	NONE
};


void Shader::setShaders(const std::string& path , std::string& vertexShader, std::string& fragementShader)
{
	std::ifstream inputFile(path);
	
	if (!inputFile.is_open())
	{
		print(Message::ERROR, "Couldn't open the shader source File at:Solution/YourProject/" + path);
		ASSERT(false);
		return;
	}

	ShaderType currentShader = ShaderType::NONE;
	std::string line;
	while (std::getline(inputFile, line))
	{
		std::string line_l = stringUtils::getTolower(line);
		if (line_l.find("#shader") != std::string::npos)
		{
			if (line_l.find("vertex") != std::string::npos)
			{
				currentShader = ShaderType::VERTEX;
			}
			else if (line_l.find("fragment") != std::string::npos)
			{
				currentShader = ShaderType::FRAGMENT;
			}
		}
		else
		{
			if (currentShader == ShaderType::VERTEX)
			{
				vertexShader += line + "\n";
			}else if (currentShader == ShaderType::FRAGMENT)
			{
				fragementShader += line + "\n";
			}
		}
	}

}