#include "IndexBuffer.h"
#include "GLDebugUtils.h"
#include "GLEW/glew.h"

IndexBuffer::IndexBuffer(const void* data,const int count):m_count(count)
{
	glCall(glGenBuffers(1, &m_RendererID));
	Bind();
	glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data)*count, data, GL_STATIC_DRAW));

}
IndexBuffer::~IndexBuffer()
{
	glCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}
void IndexBuffer::UnBind()
{
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}