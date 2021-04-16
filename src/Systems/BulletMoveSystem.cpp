#include "BulletMoveSystem.h"
#include "../Components/Bullet.h"
#include "../Components/Transform.h"
#include "../Components/Velocity.h"

void UpdateBullet(Registry& registry, float dt)
{
	const float dtSecs = dt / 1000.0f;
	auto bullets = registry.view<BulletComponent, VelocityComponent, TransformComponent>();
	auto positions = registry.view<TransformComponent>();

	for (auto entity : bullets)
	{
		auto [bullet, vel, transform] = bullets.get<BulletComponent, VelocityComponent, TransformComponent>(entity);
		if (bullet.target == entt::null)
		{
			//TODO: just move it in its direction.
			transform.pos += vel.dir * vel.speed * dtSecs;
			continue;
		}

		if (!positions.contains(bullet.target)) //Target does not exist anymore so destroy bullet
		{
			registry.destroy(entity);
			continue;
		}

		const glm::vec3 dest = positions.get<TransformComponent>(bullet.target).pos;
		const glm::vec3 dir = glm::normalize(dest - transform.pos);
		vel.dir = dir;
		transform.pos += vel.speed * dir * dtSecs;


	}
	
}
