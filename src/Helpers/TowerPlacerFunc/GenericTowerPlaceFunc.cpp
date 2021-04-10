#include "GenericTowerPlaceFunc.h"

#include "../../Components/Transform.h"
#include "../../Components/SimpleRender.h"
#include "../../Components/Scale.h"
#include "../../Components/Targeter.h"

#include "../../Helpers/TowerPlacer.h"
#include "../../Helpers/MakeCube.h"

namespace Tower
{
	entt::entity PlaceGenericTower(Registry& registry, glm::vec3 pos) //I should probably create a damage component as well 
	{
		const entt::entity tower = registry.create();
		const int index = Tower::FindGridIndex(pos);
		const float scale = (float)(TERRAIN_BOX_WIDTH / 2);
		registry.emplace<TransformComponent>(tower, pos);
		registry.emplace<SimpleRenderComponent>(tower, GetCubeBuffer(), GetCubeVertexCount());
		registry.emplace<ScaleComponent>(tower, scale, scale, scale);
		registry.emplace<TargeterComponent>(tower, 0, 2.5f);
		
		//TODO: Create a damage component to allow towers to be affected by other buffs as well etc.

		return tower;
	}

}
