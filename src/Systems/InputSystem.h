#pragma once
#include "../SingleIncludes/ecs.h"
#include <math.h>
#include "../Helpers/InputHandler.h"
#include "../Helpers/InputFunctions.h"
/*
	Deals with updating and operating on input states every frame
*/


namespace Input
{
	//This function will also deal with updating the camera if the mouse is free too.
	void UpdateInputStates(Registry& registry, float dt);
	void InitInputSystem(Registry& registry);
}

