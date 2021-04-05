#include "WaveHelpers.h"

#include "../Components/Spawner.h"
#include "../Components/Transform.h"
#include "../Components/WaveTimer.h"

#include "../Helpers/EnemySpawnFunc/WaveArrays.h"
#include "../Helpers/TowerPlacer.h"

namespace Waves
{
	void CreateSpawner(Registry& registry, const glm::vec3& pos)
	{
		const entt::entity spawner = registry.create();
		const XZ gridPos = Tower::FindGridBox(pos);
		registry.emplace<TransformComponent>(spawner, glm::vec3{ gridPos.x, 0.0f, gridPos.z });
		const float* times = WAVE_ONE_ENEMIES_TIMES.data();
		const int* types = WAVE_ONE_ENEMIES_TYPES.data();
		const int* num = WAVE_ONE_ENEMIES_COUNT.data();
		const int count = WAVE_ONE_ENEMIES_COUNT.size();
		registry.emplace<SpawnerComponent>(spawner, num, types, times, count);
		registry.emplace<WaveTimerComponent>(spawner, 0.5f);



	}

}
