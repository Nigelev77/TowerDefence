#pragma once

#include "glm/glm.hpp"
#include "../SingleIncludes/ecs.h"

struct TransitionLineComponent
{
	entt::entity target;
	glm::vec3 line;
	TransitionLineComponent()
		: line{0.0f, 0.0f, 0.0f}, target{entt::null}
	{}
	TransitionLineComponent(entt::entity target)
		: target{target}, line{0.0f, 0.0f, 0.0f}
	{}
	TransitionLineComponent(glm::vec3 l, entt::entity t)
		: target{t}, line{l}
	{}
};
