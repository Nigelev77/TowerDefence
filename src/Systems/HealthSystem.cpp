#include "HealthSystem.h"

#include "../Components/Enemy.h"
#include "../Components/Health.h"
#include "../Components/Dead.h"
#include "../Components/Reward.h"

#include "../Helpers/MoneyHelpers.h"



void UpdateHealth(Registry& registry, float dt)
{
	auto enemyHealths = registry.view<EnemyComponent, HealthComponent>();
	auto rewardEnemies = registry.view<RewardComponent>();

	for (auto entity : enemyHealths)
	{
		auto& health = enemyHealths.get<HealthComponent>(entity);
		if (health.health <= 0.0f)
		{
			if (rewardEnemies.contains(entity)) Money::TransferToPlayer(registry, entity);
			registry.emplace<DeadComponent>(entity);
		}
	}

}
