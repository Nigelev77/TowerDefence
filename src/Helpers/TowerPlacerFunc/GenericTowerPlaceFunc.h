#pragma once
#include "../../SingleIncludes/ecs.h"
#include "glm/glm.hpp"

typedef void(*TOWER_FACTORY)(Registry&, glm::vec3);

const static std::vector<TOWER_FACTORY> TowerFactories =
{
	&Tower::PlaceGenericTower
};

namespace Tower
{

	void PlaceGenericTower(Registry& registry, glm::vec3 pos);


}
