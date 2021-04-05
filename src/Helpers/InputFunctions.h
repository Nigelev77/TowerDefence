#pragma once
#include "GLFW/glfw3.h"
#include "../SingleIncludes/ecs.h"

namespace Input
{
	void KeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods);
	void MousePosInput(GLFWwindow* window, double x, double y);
	void MouseButtonInput(GLFWwindow* window, int button, int action, int mods);
	void WindowResizeInput(GLFWwindow* window, int width, int height);
	
	void SetRegistry(Registry& registry);


}