#include "PlacementSystem.h"
//Components
#include "../Components/SimpleRender.h"
#include "../Components/Transform.h"
#include "../Components/Scale.h"


#include "../Helpers/MakeCube.h"
#include "../Helpers/TowerPlacerFunc/TowerPlaceFunc.h"
#include "../Helpers/PathFinding.h"


static entt::entity SelectorEntity;
static int currentTower = 0;



void PlaceInit(Registry& registry)
{
	SelectorEntity = registry.create();
	registry.emplace<TransformComponent>(SelectorEntity);
	registry.emplace<SimpleRenderComponent>(SelectorEntity, GetCubeBuffer(), GetCubeVertexCount());
	registry.emplace<ScaleComponent>(SelectorEntity, TERRAIN_BOX_WIDTH, TERRAIN_BOX_WIDTH, TERRAIN_BOX_WIDTH);

	Terrain::TowerBoundaries = TOWER_GRID_WIDTH * TERRAIN_BOX_WIDTH;

}

void UpdatePlacer(Registry& registry, float dt)
{

	static int towerFuncIndex = 0;
	const Camera& cam = registry.ctx<Camera>();
	InputStates& input = registry.ctx<InputStates>();
	TransformComponent& transform = registry.get<TransformComponent>(SelectorEntity);
	
	//TODO: Only build in build mode


	



	const glm::vec3 dir{ Tower::GetLookVectorFromMatrix(cam.m_viewMat, cam.m_Proj) };
	if (dir.y >= 0.0f) return; //dividing by zero later
	const glm::vec3& pos = cam.m_Pos;

	//finding the position the vector has when at y=0
	const float scalar = -pos.y / dir.y;
	const glm::vec3 finalPos = pos + scalar * dir;
	const XZ gridPos = Tower::FindGridBox(finalPos); 

	if (gridPos.x ==-1|| gridPos.z ==-1)
	{
		transform.pos.x = -1000.0f;
		transform.pos.y = -1000.0f;
		return;
	}
	else
	{
		transform.pos.x = gridPos.x;
		transform.pos.y = TERRAIN_BOX_WIDTH / 2;
		transform.pos.z = gridPos.z;
	}

	//TODO: Only allow this when the player in build mode
	if (input.LButton)
	{
		if (Tower::AttemptTowerPlace(transform.pos))
		{
			//Place Tower
			const entt::entity tower = TowerFactories[currentTower](registry, transform.pos);
			const int index = Tower::FindGridIndex(transform.pos);
			input.LButton = false;

			if (tower == entt::null)
			{
				Tower::TowerGrid.towerGrid[index].occupied = false; //Unsuccessful place
				return;

			}

			if (!Path::RecalculatePath(registry)) //Could do this before placed
			{
				registry.destroy(tower);
				Tower::TowerGrid.towerGrid[index].occupied = false;
			}
			

		}
	}
	return;

}
