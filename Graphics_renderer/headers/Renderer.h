#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

class Renderer
{
private:

public:
	static void Draw(
		const VertexArray& vao,
		const IndexBuffer& ibo, 
		const Shader& shader);

	void Clear() const;


};