#pragma once
#include <string>
#include "GLEW/glew.h"

class Texture
{
public:
	Texture(std::string imageFilePath, unsigned int slot = 0,GLint texture_filter_param = GL_LINEAR);
	~Texture();
	void Bind() const;
	void UnBind() const;

private:
	unsigned int m_RendererID;
	unsigned char* m_ImageData;
	unsigned int m_TexSlot = 0;//default to GL_TEXTURE0
};