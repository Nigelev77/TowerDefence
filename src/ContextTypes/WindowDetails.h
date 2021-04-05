#pragma once
#include "GLFW/glfw3.h"

struct WindowDetails
{
	int w, h;
	GLFWwindow* window;
	bool running;
	WindowDetails(int w, int h)
		: w{w}, h{h}, window{nullptr}, running{true}
	{}
};