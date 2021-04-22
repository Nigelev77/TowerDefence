#include "EnemySpawnFunctions.h"

//Helpers
#include "../../Helpers/MakeCube.h"
#include "../../Helpers/TextureHelpers.h"

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
#include "../../Components/Billboard.h"

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

		const static unsigned int healthbarTex = GetTextureInfo("healthbar");
		
		registry.emplace<BillboardComponent>(entity, healthbarTex, glm::vec3(0.0f, 10.0f, 0.0f), glm::vec2{ 10.0f, 0.5f });

	}

}

