#include "SpawnSystem.h"

#include "../Components/WaveTimer.h"
#include "../Components/Transform.h"
#include "../Components/Spawner.h"

#include "../Helpers/EnemySpawnFunc/EnemySpawnFunctions.h"
#include "../Helpers/Logger.h"

#include <string>

namespace Spawning
{
	void UpdateWave(Registry& registry, float dt)
	{
		auto view = registry.view<TransformComponent, WaveTimerComponent, SpawnerComponent>();
		for (auto entity : view)
		{
			auto [transform, wave, spawner] = registry.get<TransformComponent, WaveTimerComponent, SpawnerComponent>(entity);
			auto& logger = registry.ctx<Logger>();
			if (spawner.spawnTypes[spawner.currentEnemy] == -1 || spawner.currentEnemy>=spawner.enemyCount)
			{
				//no enemy slots left
				registry.destroy(entity);
				logger.m_Trace->info("End of wave");
				return;
			}

			const int currentlySpawned = wave.enemyCount;


			//If spawned all current wave slot enemy count
			if (spawner.spawnNum[spawner.currentEnemy] <= currentlySpawned)
			{
				spawner.currentEnemy++;
				wave.waveTime = 0.0f;
				wave.enemyCount = 0;
				logger.m_Trace->trace("Going to enemy slot {}", spawner.currentEnemy);
				return;
			}

			//To allow a time difference between wave slot spawns.
			if (wave.enemyCount == 0)
			{
				if (wave.waveTime < spawner.spawnTimes[spawner.currentEnemy])
				{
					wave.waveTime += dt /1000.0f;
					continue;
				}
			}

			const float currentTime = wave.waveTime + dt/1000.0f;

			//spawn new enemy
			if (currentTime >= wave.spawnInterval)
			{
				wave.enemyCount++;
				const int index = spawner.spawnTypes[spawner.currentEnemy];
				SpawnFunctions[index](registry, transform.pos);
				//Only to test
				logger.m_Trace->info("Spawned enemy");
				wave.waveTime = 0.0f;
				continue;
			}
			wave.waveTime = currentTime;
		}

	}

}

