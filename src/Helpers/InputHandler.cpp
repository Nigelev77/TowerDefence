#include "InputHandler.h"
#include "../ContextTypes/WindowDetails.h"

namespace Input
{
	void SetKeyCallback(KEY_CALLBACK fun, Registry& registry)
	{
		WindowDetails& details = registry.ctx<WindowDetails>();
		glfwSetKeyCallback(details.window, fun);
	}

	void SetMouseButtonCallback(MOUSE_BUTTON_CALLBACK fun, Registry& registry)
	{
		WindowDetails& details = registry.ctx<WindowDetails>();
		glfwSetMouseButtonCallback(details.window, fun);
	}

	void SetMousePosCallback(MOUSE_POS_CALLBACK fun, Registry& registry)
	{
		WindowDetails& details = registry.ctx<WindowDetails>();
		glfwSetCursorPosCallback(details.window, fun);
	}

	void SetWindowResizeCallback(RESIZE_CALLBACK fun, Registry& registry)
	{
		WindowDetails& details = registry.ctx<WindowDetails>();
		glfwSetWindowSizeCallback(details.window, fun);
	}

	void SetMouseScrollCallback(SCROLL_CALLBACK fun, Registry& registry)
	{
		WindowDetails& details = registry.ctx<WindowDetails>();
		glfwSetScrollCallback(details.window, fun);
	}

	



}