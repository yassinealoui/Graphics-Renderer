#pragma once

#include <vector>
#include <unordered_map>

struct AttributeConfig
{
	unsigned int m_size;
	unsigned int m_type;
	unsigned int m_normalized;
	unsigned int m_offset;
	AttributeConfig(unsigned int size, unsigned int type, unsigned int normalized);

};


class VertexArrayLayout
{
private:
	unsigned int m_stride;
	std::unordered_map<std::string, unsigned int> m_attributes_cache;
public:
	std::vector<AttributeConfig> attributes;

	template<typename T>
	unsigned int addAttribute(std::string attrib_name,unsigned int size);

	template<>
	unsigned int addAttribute<float>(std::string attrib_name, unsigned int size);

	void enableAttribute(std::string attrib_name) const;

	void enableAttribute(unsigned int attrib_index) const;

	void enableAllAttributes() const;

	void refreshAllAttributes() const;

};

