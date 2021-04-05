#pragma once
#include "../SingleIncludes/ecs.h"
//For tower grid bounds, later maybe have this independent of it
#include "ManageTerrain.h"
#include <vector>
#include "glad/glad.h"
#include "glm/glm.hpp"

#define TOWER_GRID_WIDTH 8


struct XZ
{
	float x, z;
};

namespace Tower
{

	

	struct Node
	{
		bool occupied;
	};
	
	struct Grid
	{
		std::vector<Node> towerGrid;
		Grid(int size)
			: towerGrid{size}
		{}
	};

	extern Grid TowerGrid;

	bool AttemptTowerPlace(const glm::vec3& pos);
	int FindGridIndex(const glm::vec3& pos);
	XZ FindGridBox(const glm::vec3& pos);
	glm::vec3 GetLookVectorFromMatrix(const glm::mat4& view, const glm::mat4& projection);
}