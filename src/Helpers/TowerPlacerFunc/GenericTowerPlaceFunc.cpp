#include "GenericTowerPlaceFunc.h"

#include "../../Components/Transform.h"
#include "../../Components/SimpleRender.h"
#include "../../Components/Scale.h"
#include "../../Components/Target.h"

#include "../../Helpers/TowerPlacer.h"
#include "../../Helpers/MakeCube.h"

namespace Tower
{
	void PlaceGenericTower(Registry& registry, glm::vec3 pos)
	{
		const entt::entity tower = registry.create();
		const int index = Tower::FindGridIndex(pos);
		const float scale = (float)(TERRAIN_BOX_WIDTH / 2);
		registry.emplace<TransformComponent>(tower, pos);
		registry.emplace<SimpleRenderComponent>(tower, GetCubeBuffer(), GetCubeVertexCount());
		registry.emplace<ScaleComponent>(tower, scale, scale, scale);
		registry.emplace<TargetComponent>(tower, 0);
	}

}
