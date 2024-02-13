#include "../headers/VertexArrayLayout.h"
#include "../headers/GLDebugUtils.h"
#include "glew.h"

#define Log(x) std::cout << x << std::endl;


template<typename T>
unsigned int VertexArrayLayout::addAttribute(unsigned int size)
{
	Log("AttributeConfig::addAttribute -> unhandled type");
	ASSERT(false);
}

template<>
unsigned int VertexArrayLayout::addAttribute<float>(unsigned int size)
{
	AttributeConfig attribConfig(size, GL_FLOAT, GL_FALSE);
	attributes.push_back(attribConfig);
	m_stride += sizeof(float) * size;

	unsigned int attribIndex = attributes.size() - 1;
	glCall(glVertexAttribPointer(attribIndex,
		attribConfig.m_size,
		attribConfig.m_type,
		attribConfig.m_normalized,
		sizeof(float) * attribConfig.m_size,
		(const void*)0
	));
	return attribIndex;
}

void VertexArrayLayout::enableAttribute(unsigned int index)
{
	glCall(glEnableVertexAttribArray(index));
}


AttributeConfig::AttributeConfig(unsigned int size, unsigned int type, unsigned int normalized) :
		m_size(size), m_type(type), m_normalized(normalized) {}
