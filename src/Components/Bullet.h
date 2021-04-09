#pragma once
#include "../SingleIncludes/ecs.h"

struct BulletComponent
{
	entt::entity target; //Where they are seeking, it could be entt::null if no target
	BulletComponent()
		: target{entt::null}
	{}
	BulletComponent(entt::entity t)
		: target{t}
	{}
};