#include "PathFinding.h"
#define VISUALISE_PATH
#include <limits>
#include "glad/glad.h"
#include <vector>
#include <algorithm>

#include "../Components/LineStipRender.h"
#include "../Components/Transform.h"

static GLuint PathVAO = 0;
static GLuint PathVBO = 0;
static GLuint PathIBO = 0;
static unsigned int vertices = 0;
static entt::entity path = entt::null;

static std::vector<Path::XZcoord> currentPath;
static Path::XZcoord startNode{ 0,0 };
static Path::XZcoord endNode{ TOWER_GRID_WIDTH - 1, TOWER_GRID_WIDTH - 1 };

void InitPath(Registry& registry)
{
    glGenBuffers(1, &PathVBO);
    glGenBuffers(1, &PathIBO);
    glGenVertexArrays(1, &PathVAO);

    glBindVertexArray(PathVAO);

    glBindBuffer(GL_ARRAY_BUFFER, PathVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, PathIBO);
    glEnableVertexAttribArray(0);

    path = registry.create();
    registry.emplace<LineStripRenderComponent>(path, PathVAO, vertices);
    registry.emplace<TransformComponent>(path);

    return;
}


struct XYZ
{
    float x, y, z;
};

static void VisualisePath(Registry& registry)
{
    std::vector<XYZ>verts{}; //maybe put this as a C arr?
    std::vector<unsigned int> indices{};

    unsigned int ptr = 0;
    indices.push_back(ptr);

    for (const Path::XZcoord& coord : currentPath)
    {
        const float x = (coord.x + 0.5f) * TERRAIN_BOX_WIDTH;
        const float y = TERRAIN_BOX_WIDTH / 2;
        const float z = -(coord.z + 0.5f) * TERRAIN_BOX_WIDTH;

        verts.push_back({ x, y, z });
        indices.push_back(++ptr);
    }
    glBindVertexArray(PathVAO);
    glBindBuffer(GL_ARRAY_BUFFER, PathVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, PathIBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*verts.size()*3, verts.data(), GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), indices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    auto& render = registry.get<LineStripRenderComponent>(path);
    render.vertexCount = ptr;

}




//Unravels path by following last pointer on end node
static void UpdatePath(std::vector<Path::Node*>& visited)
{
    currentPath.clear(); //emptying vector from old path
    Path::Node* currentNode = visited.back();
    while (currentNode)
    {
        int x = currentNode->coord.x;
        int z = currentNode->coord.z;
        currentPath.push_back({ x, z });
        currentNode = currentNode->lastNode;
    }

    std::reverse(currentPath.begin(), currentPath.end());
}


namespace Path
{
     bool Path::RecalculatePath(Registry& registry)
    {
        static Node nodes[TOWER_GRID_WIDTH * TOWER_GRID_WIDTH];
        static std::vector<Node*> unvisited{};
        static std::vector<Node*> visited{};


        unvisited.clear();
        visited.clear();


        const auto compare = [](Node* left, Node* right)
        {
            return left->distance < right->distance;
        };


        //Filling unvisited vector with Nodes from grid
        for (int z = 0; z < TOWER_GRID_WIDTH; z++)
        {
            const int zIndex = z * TOWER_GRID_WIDTH;
            for (int x = 0; x < TOWER_GRID_WIDTH; x++)
            {
                Node& node = nodes[x + zIndex];
                //Need to put tower coord.
                node.coord = { x, z };
                node.distance = std::numeric_limits<int>::max();
                node.visited = false;
                node.lastNode = nullptr;
                unvisited.push_back(&node);
            }
        }
        Node& start = *unvisited[(size_t)startNode.x+(size_t)startNode.z*TOWER_GRID_WIDTH];
        start.distance = 0;
        
        while (!unvisited.empty())
        {
            std::sort(unvisited.begin(), unvisited.end(), compare); //TODO: Make it so I don't need to sort
            Node& currentNode = *unvisited.front();

            visited.push_back(&currentNode);
            unvisited.erase(unvisited.begin());

            const int x = currentNode.coord.x;
            const int z = currentNode.coord.z;
            if (Tower::TowerGrid.towerGrid[x + z * TOWER_GRID_WIDTH].occupied) continue;
            if (currentNode.distance == std::numeric_limits<int>::max()) return false; //Need to show error as no path can be found
            currentNode.visited = true;
            if (x == endNode.x && z == endNode.z)
            {
                //Find path as end reached
                UpdatePath(visited);
#ifdef VISUALISE_PATH
                VisualisePath(registry);
#endif
                return true;
            } //Update Path as end node reached
            if (x > 0)
            {
                Node& left = nodes[x + z * TOWER_GRID_WIDTH - 1];
                if (left.distance > currentNode.distance + 1)
                {
                    left.distance = currentNode.distance + 1;
                    left.lastNode = &currentNode;
                }
            }
            if (z > 0)
            {
                Node& bottom = nodes[x + (z - 1) * TOWER_GRID_WIDTH];
                if (bottom.distance > currentNode.distance + 1)
                {
                    bottom.distance = currentNode.distance + 1;
                    bottom.lastNode = &currentNode;
                }
            }
            if (x < TOWER_GRID_WIDTH - 1)
            {
                Node& right = nodes[x + z * TOWER_GRID_WIDTH + 1];
                if (right.distance > currentNode.distance + 1)
                {
                    right.distance = currentNode.distance + 1;
                    right.lastNode = &currentNode;
                }
            }
            if (z < TOWER_GRID_WIDTH - 1)
            {
                Node& top = nodes[x + (z + 1) * TOWER_GRID_WIDTH];
                if (top.distance > currentNode.distance + 1)
                {
                    top.distance = currentNode.distance + 1;
                    top.lastNode = &currentNode;
                }
            }
        }
        return true;
    }
}


void Path::SetStart(glm::vec3 pos)
{


}

void Path::SetEnd(glm::vec3 pos)
{
}

std::vector<Path::XZcoord>& Path::GetPath()
{
    return currentPath;
}
