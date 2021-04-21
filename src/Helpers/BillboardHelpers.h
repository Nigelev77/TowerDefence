#pragma once
#include "../SingleIncludes/ecs.h"
#include "glm/glm.hpp"

void InitBillboard();

void AttachBillboard(Registry& registry, entt::entity entity, glm::vec3 pos);
void AttachBillboard(Registry& registry, entt::entity entity, glm::vec3 pos, float size);
void AttachBillboard(Registry& registry, entt::entity entity, glm::vec3 pos, float size, unsigned int textureID);

glm::mat4 CalculateBillboardMatrix(Registry& registry, entt::entity entity);

unsigned int GetBoardID();
unsigned int GetBoardVertex();
unsigned int GetHealthbarTex();