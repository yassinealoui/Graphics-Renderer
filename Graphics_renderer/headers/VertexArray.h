#pragma once

#include "VertexArrayLayout.h"
#include "VertexBuffer.h"
#define  Log(x) std::cout << x << std::endl;
class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();


	void Bind() const;
	void UnBind() const;

	void applyLayout(const VertexBuffer& vbo , const VertexArrayLayout& layout) const;

};

