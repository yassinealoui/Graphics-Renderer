#include "VertexArrayLayout.h"
#include "GLDebugUtils.h"
#include "GLEW/glew.h"

#define Log(x) std::cout << x << std::endl;


template<typename T>
unsigned int VertexArrayLayout::addAttribute(std::string attrib_name,unsigned int size)
{
	Log("AttributeConfig::addAttribute -> unhandled type");
	ASSERT(false);
}

template<>
unsigned int VertexArrayLayout::addAttribute<float>(std::string attrib_name,unsigned int size)
{

	AttributeConfig attribConfig(size, GL_FLOAT, GL_FALSE);
	attribConfig.m_offset = m_stride;
	m_stride += sizeof(float) * size;
	attributes.push_back(attribConfig);

	unsigned int attribIndex = attributes.size() - 1;
	m_attributes_cache[attrib_name] = attribIndex;  //store the attribute index to access by name
	
	
	return attribIndex;
}

void VertexArrayLayout::enableAttribute(std::string attrib_name) const
{
	auto it = m_attributes_cache.find(attrib_name);
	if (it == m_attributes_cache.end())
	{
		Log("void VertexArrayLayout::enableAttribute(std::string attrib_name) -> ** attrib_name ** is not a registred attribute name");
		ASSERT(false);
		return;
	}
	
	unsigned int attrib_index = it->second;
	enableAttribute(attrib_index);
}

void VertexArrayLayout::enableAttribute(unsigned int attrib_index) const
{
	AttributeConfig attribConfig = attributes[attrib_index];
	glCall(glVertexAttribPointer(attrib_index,
		attribConfig.m_size,
		attribConfig.m_type,
		attribConfig.m_normalized,
		m_stride,
		(const void*)attribConfig.m_offset
	));
	glCall(glEnableVertexAttribArray(attrib_index));
}

void VertexArrayLayout::enableAllAttributes() const
{
	for (const auto& attrib : m_attributes_cache) {
		enableAttribute(attrib.second);
	}
}


AttributeConfig::AttributeConfig(unsigned int size, unsigned int type, unsigned int normalized) :
		m_size(size), m_type(type), m_normalized(normalized) {}
