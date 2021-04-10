#include "DeadSystem.h"
#include "../Components/Dead.h"

void UpdateDead(Registry& registry, float dt)
{
	auto deads = registry.view<DeadComponent>();
	for (auto entity : deads)
	{
		registry.destroy(entity); //TODO: Maybe theres a way to implement callbacks for when an enemy dies?
	}
}
