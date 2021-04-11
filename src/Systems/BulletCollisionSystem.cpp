#include "BulletCollisionSystem.h"

#include "../Components/Bullet.h"
#include "../Components/Transform.h"
#include "../Components/Health.h"
#include "../Components/Enemy.h"
#include "../Components/Damage.h"


static const float MIN_PROXIMITY = 10.0f;


void UpdateBulletCollision(Registry& registry, float dt) //TODO: NEED TO IMPLEMENT A LIFETIME COMPONENT AS WELL
{
	auto bullets = registry.view<BulletComponent, DamageComponent, TransformComponent>();
	auto enemies = registry.view<EnemyComponent, TransformComponent, HealthComponent>(); //exclude enemy deads

	for (auto entity : bullets)
	{
		auto [bullet, damage, transform] = bullets.get<BulletComponent, DamageComponent, TransformComponent>(entity);

		if (bullet.target == entt::null)
		{
			registry.destroy(entity);
			continue;
		}
		if (!enemies.contains(bullet.target))
		{
			registry.destroy(entity);
			continue;
		}
		const glm::vec3 enemyPos = enemies.get<TransformComponent>(bullet.target).pos;
		const float distance = glm::distance(enemyPos, transform.pos);
		if (distance <= MIN_PROXIMITY)
		{
			auto& enemyHealth = enemies.get<HealthComponent>(bullet.target);
			enemyHealth.health -= damage.dmg;
			registry.destroy(entity);
		}
	}

}
