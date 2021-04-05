#include "TravellerSystem.h"

#include "../Components/Path.h"
#include "../Components/Enemy.h"
#include "../Components/Transform.h"
#include "../Helpers/PathFinding.h"
#include "../Helpers/TowerPlacer.h"

#include "glm/glm.hpp"


namespace Path
{
	static float SPEED = 1.0f;

	void UpdateTravellers(Registry& registry, float dt)
	{
		registry.ctx<std::unordered_map<std::string, void*>>()["enemy_speed"] = (void*)(intptr_t)&SPEED;
		const auto& currentPath = GetPath();
		auto view = registry.view<PathComponent, TransformComponent, EnemyComponent>();
		for (auto entity : view)
		{
			auto [path, transform] = view.get<PathComponent, TransformComponent>(entity);
			if (path.nextIndex >= currentPath.size())
			{
				//Enemy has reached the end therefore destroy it
				//But actually should put a EnemyDeath component in the future so that 
				//It deducts a life
				registry.destroy(entity); //Shouldn't really destroy it here but when System developed it will
				continue;
			}
			const XZcoord currentBox = currentPath[path.boxesPast];
			const XZcoord nextBox = currentPath[path.nextIndex];
			const glm::vec3 currPos = transform.pos;
			const glm::vec3 nextCheckpoint{ (nextBox.x + 0.5f) * TERRAIN_BOX_WIDTH, 0.0f, -(nextBox.z + 0.5f) * TERRAIN_BOX_WIDTH };
			const float distancetogoSqr = (nextCheckpoint.x - currPos.x) * (nextCheckpoint.x - currPos.x) + (nextCheckpoint.z - currPos.z) * (nextCheckpoint.z - currPos.z);
			float calculatedDistSqr = distancetogoSqr - (SPEED * (dt / 1000.0f)) * (SPEED * (dt / 1000.0f));
			
			//Calculate the square distance to the midpoint of the next box
			//And subtract the square of the distance that they would travel this cycle
			//Use squared distances so that it is faster (although small rounding errors could occur)
			//if it is <0, then the enemy would move past the waypoint and so set their position to the mid-point
			//and increment values.
			if (calculatedDistSqr <= 0.0f) 
			{
				transform.pos = nextCheckpoint;
				path.boxesPast++;
				path.nextIndex++;
				continue;
			}

			//normalize may be expensive find a better way than this maybe?
			const glm::vec3 dv{ glm::normalize(nextCheckpoint - currPos)*SPEED*(dt/1000.0f) };
			transform.pos += dv;
		}
	}

}

