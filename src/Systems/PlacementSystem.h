#pragma once
#include "../SingleIncludes/ecs.h"
#include "../Helpers/TowerPlacer.h"
#include "../ContextTypes/Camera.h"
#include "../ContextTypes/InputState.h"
#include "../Components/Transform.h"
#include "../Components/SimpleRender.h"



void PlaceInit(Registry& registry);
void UpdatePlacer(Registry& registry, float dt);