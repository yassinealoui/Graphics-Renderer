#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader);
	void clear() const;
	void setClearColor(glm::vec4 clearColor);

public:
	glm::vec4 m_ClearColor;
};