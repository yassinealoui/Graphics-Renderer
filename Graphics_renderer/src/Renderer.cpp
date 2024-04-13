#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include "GLEW/glew.h"
#include "GLDebugUtils.h"


Renderer::Renderer():
	m_ClearColor(glm::vec4(0.3f, 0.7f, 0.6f, 1.0f))
{

}

Renderer::~Renderer()
{

}


void Renderer::draw(
	const VertexArray& vao, 
	const IndexBuffer& ibo, 
	const Shader& shader)
{
	glCall(glClear(GL_COLOR_BUFFER_BIT));

	// good practice to unbind first
	VertexArray::UnBind();
	IndexBuffer::UnBind();
	Shader::UnBind();

	vao.Bind();
	ibo.Bind();
	shader.Bind();
	glCall(glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr));

}

void Renderer::setClearColor(glm::vec4 clearColor)
{
	m_ClearColor = clearColor;
}

void Renderer::clear() const
{
	glCall(glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a));
	glCall(glClear(GL_COLOR_BUFFER_BIT));
}

