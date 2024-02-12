#include "../headers/VertexArray.h"
#include "../headers/common.h"



VertexArray::VertexArray()
{
    glCall(glGenVertexArrays(1, &m_RendererID));
    Bind();
}


VertexArray::~VertexArray()
{
    glCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const
{
    glCall(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind() const
{
    glCall(glBindVertexArray(0));
}

