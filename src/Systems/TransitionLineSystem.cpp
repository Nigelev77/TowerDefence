#include "TransitionLineSystem.h"

#include "../Components/Transform.h"
#include "../Components/TransitionLine.h"

void UpdateTransitionalLines(Registry& registry, float dt)
{
	auto targets = registry.view<TransformComponent>();
	auto lines = registry.view<TransitionLineComponent, TransformComponent>();

	for (auto entity : lines)
	{
		auto [line, transform] = lines.get<TransitionLineComponent, TransformComponent>(entity);
		if (line.target == entt::null) continue;
		if (!targets.contains(line.target))
		{
			line.target = entt::null;
			line.line = { 0.0f, 0.0f, 0.0f };
			continue;
		}
		const auto& targetPos = targets.get<TransformComponent>(line.target);
		line.line = targetPos.pos - transform.pos;
	}

}
