#include "TargettingSystem.h"

#include "../Components/Targeter.h"
#include "../Components/Enemy.h"
#include "../Components/Target.h"
#include "../Components/Cooldown.h"

#include <algorithm>
#include "../Helpers/TowerShootFunc/TowerShootFunctions.h"


//TODO: Create a system for towers with custom targeters
void UpdateTargettingSystem(Registry& registry, float dt)
{
	if (registry.empty<EnemyComponent>()) return;
	auto view = registry.view<TargeterComponent>(entt::exclude<CooldownComponent>);
	auto targetView = registry.view<TargetComponent>();
	
	const auto e = std::max_element(targetView.begin(), targetView.end(), [&targetView](const entt::entity left, const entt::entity right)
		{
			const auto leftComp = targetView.get<TargetComponent>(left);
			const auto rightComp = targetView.get<TargetComponent>(right);
			return leftComp.ThreatLevel > rightComp.ThreatLevel;
		}
	);
	const auto threatEnemy = *e;
	if (targetView.empty()) return; //No enemies and so therefore do not shoot.

	for (auto entity : view)
	{
		auto& targeter = view.get<TargeterComponent>(entity);
		if (targeter.target == entt::null)
		{
			targeter.target = threatEnemy;
		}
		
		if (!registry.valid(targeter.target)) //Enemy is no longer alive
		{
			targeter.target = threatEnemy;
		}

		if (targeter.shootFn >= 0)
		{
			ShootFunc[targeter.shootFn](registry, entity, targeter.target);
			registry.emplace<CooldownComponent>(entity, targeter.cooldown);
		}
	}
}
