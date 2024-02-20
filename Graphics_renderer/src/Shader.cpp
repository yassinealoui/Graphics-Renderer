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
	setShadersources(path, vertexShaderSource, fragmentShaderSource);
	unsigned int vs_c = CompileShader(ShaderType::VERTEX, vertexShaderSource);
	unsigned int fs_c = CompileShader(ShaderType::FRAGMENT, fragmentShaderSource);
	
	glCall(m_renderID = glCreateProgram());
	glCall(glAttachShader(m_renderID, vs_c));
	glCall(glAttachShader(m_renderID, fs_c));

	glCall(glLinkProgram(m_renderID));
	
	/*int success;
	glGetProgramiv(m_renderID, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(m_renderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}*/


	glCall(glValidateProgram(m_renderID));

	glCall(glDeleteShader(vs_c));
	glCall(glDeleteShader(fs_c));

}

Shader::~Shader()
{
	glCall(glDeleteShader(m_renderID));
}

void Shader::Bind() const
{
	glCall(glUseProgram(m_renderID));
}

void Shader::UnBind() const
{
	glCall(glUseProgram(0));
}


void Shader::setShadersources(const std::string& path , std::string& vertexShader, std::string& fragementShader)
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


std::string enumToString(ShaderType value) {
	switch (value) {
	case VERTEX:
		return "VERTEX SHADER";
	case FRAGMENT:
		return "FRAGMENT SHADER";
	default:
		return "UNKNOWN SHADER TYPE";
	}
}



unsigned int Shader::CompileShader(ShaderType type,const std::string& source)
{
	unsigned int shaderGLType;
	if (type == ShaderType::VERTEX)
	{
		shaderGLType = GL_VERTEX_SHADER;
	}
	else if (type == ShaderType::FRAGMENT)
	{
		shaderGLType = GL_FRAGMENT_SHADER;
	}
	else
	{
		print(Message::ERROR, "no shader type specified [None]");
		ASSERT(false);
	}


	glCall(unsigned int shader = glCreateShader(shaderGLType));
	const char* source_ptr = source.c_str();
	glCall(glShaderSource(shader, 1, &source_ptr, nullptr));
	glCall(glCompileShader(shader));


	int success;
	glCall(glGetShaderiv(shader, GL_COMPILE_STATUS,&success));
	if (success == GL_FALSE)
	{
		int logLength;
		glCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength));
		char* infoLog = (char *)alloca(sizeof(char) * logLength);
		glCall(glGetShaderInfoLog(shader, logLength, &logLength, infoLog));

		print(Message::ERROR, std::string(infoLog));
		glDeleteShader(shader);
		return 0;
	}
	else
	{
		print(Message::INFO, enumToString(type) + " compiled with success ");
	}


	return shader;

}

void Shader::setUniform4f(const std::string& u_name, float v0, float v1, float v2, float v3) const
{
	Bind(); // use the program
	unsigned int location = glGetUniformLocation(m_renderID, u_name.c_str());
	glUniform4f(location, v0, v1, v2, v3);

}

void Shader::setUniform_random_4f(const std::string& u_name) const
{
	Bind(); // use the program
	unsigned int location = glGetUniformLocation(m_renderID, u_name.c_str());

	float v0 = mathUtils::getRandomFloat(0,1);
	float v1 = mathUtils::getRandomFloat(0,1);
	float v2 = mathUtils::getRandomFloat(0,1);
	float v3 = mathUtils::getRandomFloat(0,1);

	glUniform4f(location, v0, v1, v2, v3);

}