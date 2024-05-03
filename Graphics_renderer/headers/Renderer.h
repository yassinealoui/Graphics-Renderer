#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

class Renderer
{
public:
	Renderer(glm::vec4 clear_color);
	~Renderer();

	void draw(
		const VertexArrayLayout& layout,
		const VertexBuffer& vbo,
		const VertexArray& vao, 
		const IndexBuffer& ibo,
		const Shader& shader);
	void clear() const;
	void setClearColor(glm::vec4 clearColor);

public:
	glm::vec4 m_ClearColor;
};