#include "../headers/VertexBuffer.h"
#include "../headers/GLDebugUtils.h"
#include "glew.h"

//create assure Binding
VertexBuffer::VertexBuffer(const void* data) 
{
	glCall(glGenBuffers(1, &m_RendererID));
	Bind();
	glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW));
}
VertexBuffer::~VertexBuffer()
{
	glCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const 
{
	glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}
void VertexBuffer::UnBind() const
{
	glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

