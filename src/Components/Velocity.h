#pragma once
#include "glm/glm.hpp"

struct VelocityComponent
{
	glm::vec3 dir;
	float speed;

	VelocityComponent(glm::vec3 direction, float speed)
		: dir{direction}, speed{speed}
	{}

	VelocityComponent(glm::vec3 direction)
		: dir{direction}, speed{1.0f}
	{}

	VelocityComponent()
		: dir{0.0f, 0.0f, 0.0f}, speed{0.0f}
	{}

};