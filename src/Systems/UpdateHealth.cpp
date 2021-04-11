#include "UpdateHealth.h"

#include "../Components/Enemy.h"
#include "../Components/Health.h"
#include "../Components/Dead.h"

void UpdateHealth(Registry& registry, float dt)
{
	auto enemyHealths = registry.view<EnemyComponent, HealthComponent>();

	for (auto entity : enemyHealths)
	{
		auto& health = enemyHealths.get<HealthComponent>(entity);
		if (health.health <= 0.0f) registry.emplace<DeadComponent>(entity);
	}

}
