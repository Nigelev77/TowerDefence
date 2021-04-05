#include "InputFunctions.h"
#include "../ContextTypes/InputState.h"
#include "../ContextTypes/WindowDetails.h"

#include <iostream>

namespace Input
{
	static Registry* externalReg; //Since the registry will be shared

	//This sets the individual bools rather than changing input state
	void KeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_REPEAT) return;
		InputStates& state = externalReg->ctx<InputStates>();
		bool release = action == GLFW_RELEASE;
		switch (key)
		{
		case GLFW_KEY_W:
			state.W = !release; break;
		case GLFW_KEY_A:
			state.A = !release; break;
		case GLFW_KEY_S:
			state.S = !release; break;
		case GLFW_KEY_D:
			state.D = !release; break;
		case GLFW_KEY_SPACE:
			state.SPACE = !release; break;
		case GLFW_KEY_Q:
			state.Q = !release; break;
		case GLFW_KEY_ESCAPE:
		{
			WindowDetails& details = externalReg->ctx<WindowDetails>();
			details.running = false;
			break;

		}
		}

		return;


	}
	
	//Updates the currentPos of the mouse since the InputSystem will update the lastPos. See InputSystem.cpp
	void MousePosInput(GLFWwindow* window, double x, double y)
	{

		//TODO: CALCULATE DX AND DY
		InputStates& state = externalReg->ctx<InputStates>();
		state.currPos = { x, y };


	}

	//This sets the bools, similar to KeyboardInput
	void MouseButtonInput(GLFWwindow* window, int button, int action, int mods)
	{
		//TODO: CHANGE INPUT STATES
		if (action == GLFW_REPEAT) return;
		InputStates& state = externalReg->ctx<InputStates>();
		bool released = (action == GLFW_RELEASE);
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			state.LButton = !released; break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			state.RButton = !released; break;
		}

	}
	
	void WindowResizeInput(GLFWwindow* window, int width, int height)
	{
		WindowDetails& details = externalReg->ctx<WindowDetails>();
		details.h = height;
		details.w = width;
		glViewport(0, 0, width, height);
	}


	//Sets the registry pointer for this file
	void SetRegistry(Registry& registry)
	{
		externalReg = &registry;
	}

}