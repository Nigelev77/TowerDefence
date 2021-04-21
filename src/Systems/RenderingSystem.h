#pragma once

/*
Basic Rendering

*/

#include "../SingleIncludes/ecs.h"
#include "../Helpers/ManageTerrain.h"
#include "glad/glad.h"

void UpdateRendering(Registry& registry, float dt);
void InitRendering(Registry& registry);