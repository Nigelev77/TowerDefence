#pragma once

#include "../SingleIncludes/ecs.h"

namespace Path
{
	/*
	*Update the position of entities which follow the path
	*/
	void UpdateTravellers(Registry& registry, float dt);

}