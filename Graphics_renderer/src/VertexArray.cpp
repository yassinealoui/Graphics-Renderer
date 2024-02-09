#include "../headers/VertexArray.h"
#include "../headers/common.h"

//
//VertexArray::VertexArray(const void* data, const int size)
//{
//	
//}
VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexArray::Bind() const
{
	glBindBuffer(GL_VERTEX_ARRAY, m_RendererID);
}
void VertexArray::UnBind() const
{
	glBindBuffer(GL_VERTEX_ARRAY, 0);
}