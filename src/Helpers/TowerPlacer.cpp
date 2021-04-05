#include "TowerPlacer.h"
#include "../ContextTypes/Camera.h"
#include <numeric>
#include <iostream>
namespace Tower
{
	extern Grid TowerGrid{ TOWER_GRID_WIDTH * TOWER_GRID_WIDTH };
	const static int GridBoxNum = TOWER_GRID_WIDTH; //The number of grid boxes the playing area's width is
	const static int GridBoxWidth = TERRAIN_BOX_WIDTH; //The width of an individual grid space

	/**
	*@brief calculates the grid space index on the playing grid that the position is in.
	* 
	*
	*@returns The index into the towerGrid of the space or -1 if not in the space.
	*/
	int FindGridIndex(const glm::vec3& pos)
	{
		const float x = pos.x;
		const float z = pos.z;
		if (x < 0.0f || z > 0.0f) return -1; //z>0.0f due to the LHSness of the game world
		//TODO: Need to make the playing grid a bit more of a flexible thing so that bounds can be determined from them such as how many 
		//grid spaces, how wide they are and the start and end coordinates. However, for now this is fine.
		const int xIndex = (int)(x/TERRAIN_BOX_WIDTH);
		const int zIndex = (int)(std::abs(z)/TERRAIN_BOX_WIDTH);
		if (xIndex > GridBoxNum-1 || zIndex > GridBoxNum-1) return -1;
		return xIndex + zIndex * GridBoxNum;
	}

	/**
	*@brief calculates the grid space world position on the playing grid that the position is in.
	*
	*
	*@returns The position of middle of the grid space or -1 if not in grid
	*/
	XZ FindGridBox(const glm::vec3& pos)
	{
		const float x = pos.x;
		const float z = pos.z;
		if (x < 0.0f || z > 0.0f) return { -1, -1 }; //z>0.0f due to the LHSness of the game world
		//TODO: Need to make the playing grid a bit more of a flexible thing so that bounds can be determined from them such as how many 
		//grid spaces, how wide they are and the start and end coordinates. However, for now this is fine.
		const int xIndex = (int)(x/(float)TERRAIN_BOX_WIDTH); //for now
		const int zIndex = std::abs(z) / (float)TERRAIN_BOX_WIDTH; //for now
		if (xIndex > GridBoxNum-1 || zIndex > GridBoxNum-1) return { -1, -1 };
		//return { xIndex * ((float)GridBoxWidth + 0.5f), -zIndex * ((float)GridBoxWidth + 0.5f) }; NEED TO FIX THIS
		return { (xIndex+0.5f)*GridBoxWidth, -(zIndex+0.5f)*GridBoxWidth};
	}

	//This might become obsolete if I just check mouse click in the placement system
	//3/3/2021 This is to attempt to place tower
	bool AttemptTowerPlace(const glm::vec3& pos)
	{
		const int index = FindGridIndex(pos);
		if (index < 0) return false;
		if (TowerGrid.towerGrid[index].occupied)
		{
			
			return false;
		}

		TowerGrid.towerGrid[index].occupied = true;
		return true;

	}


	

	/**
	*Obtains the look vector given a view and projection matrix.
	*@return direction vector
	*/
	glm::vec3 GetLookVectorFromMatrix(const glm::mat4& view, const glm::mat4& projection	)
	{
		static const glm::mat4 inverseProj = glm::inverse(projection);
		const glm::mat4 inverseView = glm::inverse(view);
		const glm::vec4 clip = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
		glm::vec4 eyeRay = inverseProj * clip;
		eyeRay.w = 0.0f;
		eyeRay.z = -1.0f; //Maybe go to try to understand how this actually works?
		const glm::vec4 worldRay4 = inverseView * eyeRay;
		const glm::vec3 dir{ glm::normalize(glm::vec3(worldRay4.x, worldRay4.y, worldRay4.z)) };
		return dir;
	}

}