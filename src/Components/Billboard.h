#pragma once
#include "glm/glm.hpp"

struct BillboardComponent
{
	unsigned int textureID;
	glm::vec3 displacement;
	float size;

	BillboardComponent(unsigned int texture, float s)
		: textureID{texture}, displacement{0.0f, 0.0f, 0.0f}, size{s}
	{}

	BillboardComponent(unsigned int texture, glm::vec3 dis, float s)
		: textureID{texture}, displacement{dis}, size{s}
	{}

	BillboardComponent(unsigned int texture, glm::vec3 dis)
		: textureID{texture}, displacement{dis}, size{1.0f}
	{}

	BillboardComponent()
		: textureID{0}, displacement{0.0f, 0.0f, 0.0f}, size{0.0f}
	{}

	BillboardComponent(glm::vec3 pos)
		: textureID{0}, displacement{pos}, size{1.0f}
	{}

};
