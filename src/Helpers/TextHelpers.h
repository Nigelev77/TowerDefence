#pragma once
#include "../SingleIncludes/ecs.h"
#include "glm/glm.hpp"

struct TextBounds
{
	glm::vec2 tr, tl, br, bl;
};

glm::mat4 ScaleQuad(float width, float height);

TextBounds CalculateBounds(Registry& registry, char c);
