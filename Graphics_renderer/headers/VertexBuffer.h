#pragma once

class VertexBuffer
{
private:
	unsigned int  m_RendererID;
public:
	VertexBuffer(const void* data , int size);
	~VertexBuffer();


	void Bind() const;
	static void UnBind();
};
