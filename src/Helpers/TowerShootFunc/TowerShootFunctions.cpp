#include "TowerShootFunctions.h"

#include "../../Components/Bullet.h"
#include "../../Components/Transform.h"
#include "../../Components/Velocity.h"
#include "../../Components/Damage.h"
#include "../../Components/Lifetime.h"
#include "../../Components/SimpleRender.h"
#include "../../Components/Scale.h"

#include "../../Helpers/MakeCube.h"

static const float GENERIC_SPEED = 5.0f;
static const float GENERIC_DAMAGE = 10.0f;
static const float GENERIC_LIFETIME = 15.0f;


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
		registry.emplace<LifetimeComponent>(bullet, GENERIC_LIFETIME);
		//Need to figure out how these bullet should appear
		//I stuck with just a cube for now
		registry.emplace<SimpleRenderComponent>(bullet, GetCubeBuffer(), GetCubeVertexCount());
		registry.emplace<ScaleComponent>(bullet, 1.0f);
		
	}


}

