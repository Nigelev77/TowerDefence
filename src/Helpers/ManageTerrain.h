#pragma once
#include "../SingleIncludes/ecs.h"




#define TERRAIN_SIZE 32
#define TERRAIN_BOX_NUM 31
#define TERRAIN_BOX_WIDTH 16

namespace Terrain
{
	extern float TowerBoundaries;

	void CreateTerrain(Registry& registry);
	void RenderTerrain(Registry& registry);
	void InitTerrain(Registry& registry);
}
