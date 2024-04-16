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
	const VertexArrayLayout& layout,
	const VertexBuffer& vbo,
	const VertexArray& vao, 
	const IndexBuffer& ibo, 
	const Shader& shader)
{
	//glCall(glClear(GL_COLOR_BUFFER_BIT));

	// good practice to unbind first
	VertexBuffer::UnBind();
	VertexArray::UnBind();
	IndexBuffer::UnBind();
	Shader::UnBind();

	//we bind the vertex buffer too , because sometimes we have multiple objects in the scene
	//thus we need to call refreshAllAttributes to update the glVertexAttribPointer to the new set of vertces


	vbo.Bind();

	// the vao must be bound , because glVertexAttribPointer will through an invalid operation error
	vao.Bind();
	layout.refreshAllAttributes();
	//


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

