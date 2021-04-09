#pragma once
#include "../SingleIncludes/ecs.h"

void UpdateCooldowns(Registry& registry, float dt); //Iterates and subtracts the time elapsed for the cooldowns;