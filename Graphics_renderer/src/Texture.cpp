#include "Texture.h"
#include "GLDebugUtils.h";

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "GLEW/glew.h"


#define Log(x) std::cout << x << std::endl;

//Todo:: add glCall() for debugging

Texture::Texture(std::string imageFilePath,unsigned int slot,GLint texture_filter_param):m_TexSlot(slot)
{
	int x, y, n;

	stbi_set_flip_vertically_on_load(true);
	m_ImageData = stbi_load(imageFilePath.c_str(), &x, &y, &n, 4);
	if (m_ImageData == nullptr)
	{
		std::string reason = stbi_failure_reason();
		print(Message::ERROR, "Couldn't load image at \"" + imageFilePath + "\"");
		Log("Reaon : " + reason);
		ASSERT(false);
	}

	glCall(glGenTextures(1, &m_RendererID));
	Bind();

	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_filter_param));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_filter_param));

	glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_ImageData));

	stbi_image_free(m_ImageData);
}

Texture::~Texture()
{
	glCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind() const 
{
	glCall(glActiveTexture(GL_TEXTURE0 + m_TexSlot));
	glCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}


void Texture::UnBind() const
{
	glCall(glBindTexture(GL_TEXTURE_2D, 0));
}