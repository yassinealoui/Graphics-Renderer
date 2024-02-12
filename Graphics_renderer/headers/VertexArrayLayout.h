#pragma once

#include <vector>

struct AttributeConfig
{
	unsigned int m_size;
	unsigned int m_type;
	unsigned int m_normalized;

	AttributeConfig(unsigned int size, unsigned int type, unsigned int normalized);

};


class VertexArrayLayout
{
private:
	unsigned int m_stride;
public:
	std::vector<AttributeConfig> attributes;

	template<typename T>
	unsigned int addAttribute(unsigned int size);

	template<>
	unsigned int addAttribute<float>(unsigned int size);

	void enableAttribute(unsigned int index);

};

