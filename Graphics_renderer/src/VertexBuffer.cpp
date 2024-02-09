#include "../headers/VertexBuffer.h"
#include "../headers/common.h"

//create assure Binding
VertexBuffer::VertexBuffer(const void* data,const int size) 
{
	glGenBuffers(1, &m_RendererID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const 
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}
void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

