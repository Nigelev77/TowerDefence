#pragma once
#include "GLFW/glfw3.h"
#include "../SingleIncludes/ecs.h"

namespace Input
{
	using KEY_CALLBACK = GLFWkeyfun;
	using MOUSE_BUTTON_CALLBACK = GLFWmousebuttonfun;
	using MOUSE_POS_CALLBACK = GLFWcursorposfun;
	using RESIZE_CALLBACK = GLFWwindowsizefun;
	using SCROLL_CALLBACK = GLFWscrollfun;



	void SetKeyCallback(KEY_CALLBACK fun, Registry& registry);
	void SetMouseButtonCallback(MOUSE_BUTTON_CALLBACK fun, Registry& registry);
	void SetMousePosCallback(MOUSE_POS_CALLBACK fun, Registry& registry);
	void SetWindowResizeCallback(RESIZE_CALLBACK fun, Registry& registry);
	void SetMouseScrollCallback(SCROLL_CALLBACK fun, Registry& registry);
}