#include "EnemySpawnFunctions.h"

//Helpers
#include "../../Helpers/MakeCube.h"


//Components
#include "../../Components/Lives.h"
#include "../../Components/Enemy.h"
#include "../../Components/Transform.h"
#include "../../Components/Velocity.h"
#include "../../Components/Target.h"
#include "../../Components/SimpleRender.h"
#include "../../Components/Scale.h"
#include "../../Components/Path.h"
#include "../../Components/Health.h"

static float GENERIC_HEALTH = 100.0f;

namespace Enemy
{
	void CreateGenericEnemy(Registry& registry, glm::vec3& position)
	{
		//create generic enemy

		const auto entity = registry.create();
		registry.emplace<TransformComponent>(entity, position);
		registry.emplace<ScaleComponent>(entity, 8.0f);
		registry.emplace<VelocityComponent>(entity);
		registry.emplace<PathComponent>(entity);
		registry.emplace<TargetComponent>(entity);
		registry.emplace<LivesComponent>(entity, 1);
		registry.emplace<EnemyComponent>(entity);
		registry.emplace<SimpleRenderComponent>(entity, GetCubeBuffer(), GetCubeVertexCount());
		registry.emplace<HealthComponent>(entity, GENERIC_HEALTH);
	}

}

