#pragma once


class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_count;
public:
	IndexBuffer(const void* data, const int count);
	~IndexBuffer();

	unsigned int getCount() const { return m_count; };
	
	void Bind() const;
	static void UnBind();
};

