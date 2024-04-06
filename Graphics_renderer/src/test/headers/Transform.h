#pragma once

#include "glm/glm.hpp"


class Transform
{
public:
	glm::vec3 getTranslation()const { return m_Translation; };
	glm::vec3 getRotation()const { return m_Rotation; };
	glm::vec3 getScale()const { return m_Scale; };


	void setTranslation(const glm::vec3& translation) { m_Translation = translation; };
	void setRotation(const glm::vec3& rotation) { m_Rotation = rotation; };
	void setScale(const glm::vec3& scale) { m_Scale = scale; };


private:
	glm::vec3 m_Translation;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
};