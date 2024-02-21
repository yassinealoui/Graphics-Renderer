#include "../headers/VertexBuffer.h"
#include "../headers/IndexBuffer.h"
#include "../headers/Shader.h"
#include "../headers/Renderer.h"
#include <glew.h>
#include "../headers/GLDebugUtils.h"



void Renderer::Draw(
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

void Renderer::Clear() const
{
	glCall(glClear(GL_COLOR_BUFFER_BIT));
}

