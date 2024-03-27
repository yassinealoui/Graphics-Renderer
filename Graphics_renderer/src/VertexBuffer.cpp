#include "VertexBuffer.h"
#include "GLDebugUtils.h"
#include "GLEW/glew.h"

//create assure Binding
VertexBuffer::VertexBuffer(const void* data, int size) 
{
	glCall(glGenBuffers(1, &m_RendererID));
	Bind();
	glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
VertexBuffer::~VertexBuffer()
{
	glCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const 
{
	glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}
void VertexBuffer::UnBind()
{
	glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

