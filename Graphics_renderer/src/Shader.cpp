#include "Shader.h"
#include "GLDebugUtils.h"
#include "GLEW/glew.h"
#include "Utils.h"
#include <fstream>


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
	
	int success;
	glGetProgramiv(m_renderID, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(m_renderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}


	glCall(glValidateProgram(m_renderID));

	glCall(glDeleteShader(vs_c));
	glCall(glDeleteShader(fs_c));

}

Shader::~Shader()
{
	glCall(glDeleteProgram(m_renderID));
	//print(Message::INFO, std::to_string(m_renderID) + " is deleted !");
}

void Shader::Bind() const
{
	glCall(glUseProgram(m_renderID));
}

void Shader::UnBind()
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
		glCall(glDeleteShader(shader));
		return 0;
	}
	else
	{
		//print(Message::INFO, enumToString(type) + " compiled with success ");
	}


	return shader;

}

void Shader::setUniform4f(const std::string& u_name, float v0, float v1, float v2, float v3) const
{
	Bind(); // use the program
	glCall(unsigned int location = glGetUniformLocation(m_renderID, u_name.c_str()));
	glCall(glUniform4f(location, v0, v1, v2, v3));

}

void Shader::setUniform1i(const std::string& u_name, unsigned int value) const 
{
	Bind(); // use the program
	glCall(unsigned int location = glGetUniformLocation(m_renderID, u_name.c_str()));
	glCall(glUniform1i(location, value));
}

void Shader::setUniformMat4(const std::string& u_name, const glm::mat4& mat) const
{
	Bind(); // use the program
	glCall(unsigned int location = glGetUniformLocation(m_renderID, u_name.c_str()));
	glCall(glUniformMatrix4fv(location,1,GL_FALSE, &mat[0][0]));
}

void Shader::setUniform_random_4f(const std::string& u_name) const
{
	Bind(); // use the program
	glCall(int location = glGetUniformLocation(m_renderID, u_name.c_str()));
	if (location == -1)
	{
		Log("uniform \"" + u_name + "\" doesn't exsits !");
		ASSERT(false);
	}
	float v0 = mathUtils::getRandomFloat(0,1);
	float v1 = mathUtils::getRandomFloat(0,1);
	float v2 = mathUtils::getRandomFloat(0,1);
	float v3 = mathUtils::getRandomFloat(0,1);

	glCall(glUniform4f(location, v0, v1, v2, v3));

}