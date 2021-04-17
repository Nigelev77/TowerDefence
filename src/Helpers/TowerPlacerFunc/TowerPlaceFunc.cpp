#include "TowerPlaceFunc.h"

#include "../../Components/Transform.h"
#include "../../Components/SimpleRender.h"
#include "../../Components/Scale.h"
#include "../../Components/Targeter.h"
#include "../../Components/Damage.h"
#include "../../Components/TransitionLine.h"

#include "../../Helpers/TowerPlacer.h"
#include "../../Helpers/MakeCube.h"
#include "../../Helpers/MoneyHelpers.h"


#define GENERIC_INDEX  0
#define LASER_INDEX 1

static const float LASER_DAMAGE = 5.0f;


namespace Tower
{
	entt::entity PlaceGenericTower(Registry& registry, glm::vec3 pos) //I should probably create a damage component as well 
	{
		if (!Money::AttemptWithdraw(registry, TowerCosts[GENERIC_INDEX])) return entt::null; //Not enough money
		const entt::entity tower = registry.create();
		const int index = Tower::FindGridIndex(pos);
		const float scale = (float)(TERRAIN_BOX_WIDTH / 2);
		registry.emplace<TransformComponent>(tower, pos);
		registry.emplace<SimpleRenderComponent>(tower, GetCubeBuffer(), GetCubeVertexCount());
		registry.emplace<ScaleComponent>(tower, scale, scale, scale);
		registry.emplace<TargeterComponent>(tower, GENERIC_INDEX, 2.5f);


		
		//TODO: Create a damage component to allow towers to be affected by other buffs as well etc.

		return tower;
	}

	entt::entity PlaceLaserTower(Registry& registry, glm::vec3 pos)
	{
		if (!Money::AttemptWithdraw(registry, TowerCosts[LASER_INDEX])) return entt::null;
		const entt::entity tower = registry.create();
		const int index = Tower::FindGridIndex(pos);
		const float scale = (float)(TERRAIN_BOX_WIDTH / 2); //TODO: Just make this a constant 
		registry.emplace<TransformComponent>(tower, pos);
		registry.emplace<SimpleRenderComponent>(tower, GetCubeBuffer(), GetCubeVertexCount());
		registry.emplace<ScaleComponent>(tower, scale, scale, scale);
		registry.emplace<TargeterComponent>(tower, LASER_INDEX, 0.25f);

		//Create "Laser" that the tower will have so it's "laser" will always exist but will only appear when shooting at an enemy
		//And when shooting, the tower doesn't need to create any new entity and only needs to do a few updates on the laser related components.
		registry.emplace<DamageComponent>(tower, LASER_DAMAGE);
		registry.emplace<TransitionLineComponent>(tower);
		

		return tower;
	}



}
