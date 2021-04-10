#include "LifetimeSystem.h"
#include "../Components/Lifetime.h"
#include "../Components/Dead.h"

void UpdateLifetimes(Registry& registry, float dt)
{
	const float dtSecs = dt / 1000.0f;
	
	auto lifetimes = registry.view<LifetimeComponent>();
	for (auto entity : lifetimes)
	{
		auto life = lifetimes.get<LifetimeComponent>(entity);
		life.lifetime -= dtSecs;
		if (life.lifetime <= 0.0f)
		{
			//registry.destroy(entity); //Or should it be better to put it in a "dead" state? probably
			registry.emplace<DeadComponent>(entity);
		}
	}
}
