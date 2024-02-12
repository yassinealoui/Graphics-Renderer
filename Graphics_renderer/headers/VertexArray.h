#pragma once

#include "VertexArrayLayout.h"

#define  Log(x) std::cout << x << std::endl;
class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArrayLayout m_layout;
	VertexArray();
	~VertexArray();


	void Bind() const;
	void UnBind() const;

};

