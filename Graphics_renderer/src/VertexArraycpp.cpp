#include "../headers/VertexArray.h"
#include "../headers/common.h"



VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
    Bind();
}


VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::UnBind() const
{
    glBindVertexArray(0);
}

