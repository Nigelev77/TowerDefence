#pragma once
#include "../../SingleIncludes/ecs.h"
#include "glm/glm.hpp"

typedef entt::entity(*TOWER_FACTORY)(Registry&, glm::vec3);

namespace Tower
{

	entt::entity PlaceGenericTower(Registry& registry, glm::vec3 pos);
	entt::entity PlaceLaserTower(Registry& registry, glm::vec3 pos);

}
const static std::vector<TOWER_FACTORY> TowerFactories =
{
	&Tower::PlaceGenericTower, &Tower::PlaceLaserTower
};

const static std::vector<int> TowerCosts =
{
	100, 250
};

