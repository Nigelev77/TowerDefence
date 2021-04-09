#include "ThreatTargettingSystem.h"

#include "../Helpers/PathFinding.h"

#include "../Components/Enemy.h"
#include "../Components/Target.h"
#include "../Components/Path.h"
#include "../Components/Transform.h"

namespace Enemy
{
	//This could be done in the traveller system too?
	void UpdateThreatSystem(Registry& registry, float dt)
	{
		const std::vector<Path::XZcoord>& currpath = Path::GetPath();
		const int size = currpath.size();
		auto view = registry.view<EnemyComponent, TargetComponent, PathComponent, TransformComponent>();
		for (auto entity : view)
		{
			auto [target, path, transform] = view.get<TargetComponent, PathComponent, TransformComponent>(entity);
			if (path.nextIndex >= size) continue;
			const float ratio = path.boxesPast / size;
			const Path::XZcoord lastBox = currpath[path.nextIndex];
			const glm::vec3 lastBoxPos{ (lastBox.x + 0.5f) * TERRAIN_BOX_WIDTH, 0.0f, -(lastBox.z + 0.5f) * TERRAIN_BOX_WIDTH };
			const glm::vec3 currentPos = transform.pos;
			const float distanceSqr = (lastBoxPos.x - currentPos.x) * (lastBoxPos.x - currentPos.x) + (lastBoxPos.z - currentPos.z) * (lastBoxPos.z - currentPos.z);
			const float tileSizeSqr = TERRAIN_BOX_WIDTH*TERRAIN_BOX_WIDTH;
			target.ThreatLevel = (ratio + distanceSqr/tileSizeSqr/size) * target.ThreatMultiplier; //distanceSqr will increase as ratio increases

		}

	}

}

