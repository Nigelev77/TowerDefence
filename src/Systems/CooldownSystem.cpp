#include "CooldownSystem.h"
#include "../Components/Cooldown.h"

void UpdateCooldowns(Registry& registry, float dt)
{
	const float dtSecs = dt / 1000.0f;
	auto view = registry.view<CooldownComponent>();
	for (auto entity : view)
	{
		CooldownComponent& cd = view.get<CooldownComponent>(entity);
		cd.cd -= dtSecs;
		if (cd.cd <= 0.0f)
		{
			registry.remove<CooldownComponent>(entity);
		}
	}
}
