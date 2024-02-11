#pragma once
#include <iostream>
#include <vector>
#include "glew.h"

#define  log(x) std::cout << x << std::endl;
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

//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);

class VertexArrayLayout
{
private:
	unsigned int m_stride;
public:
	std::vector<AttributeConfig> attributes;

	template<typename T>
	unsigned int addAttribute(unsigned int size)
	{
		log("AttributeConfig::addAttribute -> unhandled type");
		ASSERT(false);
	}

	template<>
	unsigned int addAttribute<float>(unsigned int size)
	{
		AttributeConfig attribConfig(size, GL_FLOAT, GL_FALSE);
		attributes.push_back(attribConfig);
		m_stride += sizeof(float) * size;

		unsigned int attribIndex = attributes.size() - 1;
		glVertexAttribPointer(attribIndex, 
			attribConfig.m_size, 
			attribConfig.m_type,
			attribConfig.m_normalized,
			sizeof(float) * attribConfig.m_size,
			(const void*)0
		);
		return attribIndex;
	}

	void enableAttribute(unsigned int index)
	{
		glEnableVertexAttribArray(index);
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