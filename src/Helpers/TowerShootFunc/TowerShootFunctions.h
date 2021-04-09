#pragma once
#include "../../SingleIncludes/ecs.h"

#include "glm/glm.hpp"

typedef void (*SHOOT_FN)(Registry&, entt::entity, entt::entity);

namespace Tower
{
	/**
	*@brief Generic Shoot
	* @param registry - registry
	* tower - tower
	* enemey - enemy
	*/
	void GenericShoot(Registry& registry, entt::entity tower, entt::entity enemy);
}

static const SHOOT_FN ShootFunc[] =
{
	&Tower::GenericShoot
};