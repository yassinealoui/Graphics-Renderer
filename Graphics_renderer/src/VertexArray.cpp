#include "../headers/VertexArray.h"
#include "../headers/GLDebugUtils.h"
#include "glew.h"

VertexArray::VertexArray()
{
    glCall(glGenVertexArrays(1, &m_RendererID));
}


VertexArray::~VertexArray()
{
    glCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const
{
    glCall(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind() 
{
    glCall(glBindVertexArray(0));
}

void VertexArray::addBuffer(const VertexBuffer& vbo, const VertexArrayLayout& layout) const
{
    Bind();//bind the vao
    vbo.Bind(); // bind the vbo
    layout.enableAllAttributes();
}
