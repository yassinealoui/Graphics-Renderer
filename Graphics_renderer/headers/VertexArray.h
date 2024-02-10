#pragma once
#include <iostream>
#include <vector>

#define  log(x) std::cout << x << std::endl;
class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();


	void Bind() const;
	void UnBind() const;

};


//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);


class VertexArrayLayout
{
private:
	unsigned int m_stride;
public:
	std::vector<AttributeConfig> attributes;

	template<typename T>
	int addAttribute(unsigned int size)
	{
		log("AttributeConfig::addAttribute -> unhandled type");
		ASSERT(false);
	}

	template<>
	int addAttribute<float>(unsigned int size)
	{
		AttributeConfig attribConfig(size, GL_FLOAT, GL_FALSE);
		attributes.push_back(attribConfig);
		m_stride += sizeof(float) * size;

		return attributes.size() - 1; //return the index of attribute;
	}




};



struct AttributeConfig
{
	unsigned int m_size;
	unsigned int m_type;
	unsigned int m_normalized;

	AttributeConfig(unsigned int size, unsigned int type, unsigned int normalized) :
		m_size(size), m_type(type), m_normalized(normalized) {}
	
};