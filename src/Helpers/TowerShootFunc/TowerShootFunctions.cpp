#include "TowerShootFunctions.h"

#include "../../Components/Bullet.h"
#include "../../Components/Transform.h"
#include "../../Components/Velocity.h"
#include "../../Components/Damage.h"

static const float GENERIC_SPEED = 5.0f;
static const float GENERIC_DAMAGE = 10.0f;


namespace Tower
{

	void GenericShoot(Registry& registry, entt::entity tower, entt::entity enemy)
	{
		const auto pos = registry.get<TransformComponent>(tower);
		auto bullet = registry.create();
		registry.emplace<BulletComponent>(bullet, enemy);
		registry.emplace<TransformComponent>(bullet, pos.pos);
		registry.emplace<VelocityComponent>(bullet, GENERIC_SPEED);
		registry.emplace<DamageComponent>(bullet, GENERIC_DAMAGE);
		//Need to figure out how these bullet should appear
	}


}

