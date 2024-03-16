#pragma once
#include <string>

class Texture
{
public:
	Texture(std::string imageFilePath, unsigned int slot = 0);
	~Texture();
	void Bind() const;
	void UnBind() const;

private:
	unsigned int m_RendererID;
	unsigned char* m_ImageData;
	unsigned int m_TexSlot = 0;//default to GL_TEXTURE0
};