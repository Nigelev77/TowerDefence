#pragma once
#include "../../SingleIncludes/ecs.h"

#include "glm/glm.hpp"

typedef void(*ENEMY_SPAWN_FN)(Registry&, glm::vec3&);

namespace Enemy
{
	void CreateGenericEnemy(Registry& registry, glm::vec3& position);
}

static const ENEMY_SPAWN_FN SpawnFunctions[1] =
{
	&Enemy::CreateGenericEnemy
};



