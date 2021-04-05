#pragma once
#include "TowerPlacer.h"
#include <vector>
#include "glm/glm.hpp"
#include "../SingleIncludes/ecs.h"

#define PLAY_GRID_WIDTH 8


void InitPath(Registry& registry);

namespace Path
{
	struct XZcoord
	{
		int x, z;
		XZcoord(int x, int z)
			: x{x}, z{z}
		{}
		XZcoord()
			: x{-1}, z{-1}
		{}

		inline XZcoord operator-(const XZcoord& other) const
		{
			return XZcoord{ x - other.x, z - other.z };
		}

		inline bool operator==(XZ other) const
		{
			return (x == (int)other.x) && (z == (int)std::abs(other.z));
		}

		inline bool operator!=(XZ other) const
		{
			return !(operator==(other));
		}

	};

	struct Node
	{
		XZcoord coord;
		int distance;
		Node* lastNode;
		bool visited;
		Node(XZcoord coord, int dist, Node* last)
			: coord{coord}, distance{dist}, lastNode{last}, visited{false}
		{}

		Node()
			: coord{0,0}, distance{-1}, lastNode{nullptr}, visited{false}
		{}
	};


	bool RecalculatePath(Registry& registry);
	void SetStart(glm::vec3 pos);
	void SetEnd(glm::vec3 pos);
	std::vector<XZcoord>& GetPath();
}