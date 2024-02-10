#include "../headers/VertexArray.h"
#include "../headers/common.h"



VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
    Bind();
    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);

}

VertexArray::~VertexArray()
{

}

void VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::UnBind() const
{
    glBindVertexArray(0);
}



AttributeConfig::CreateAttributeConfig<T(unsigned int size)
{

}