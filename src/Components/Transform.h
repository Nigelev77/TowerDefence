#pragma once
#include "glm/glm.hpp"


struct TransformComponent
{
	glm::vec3 pos;
	TransformComponent(glm::vec3 pos)
		: pos{pos}
	{}

	TransformComponent()
		: pos{0.0f, 0.0f, 0.0f}
	{}
};