#include "InputSystem.h"
#include "../ContextTypes/Camera.h"
#include "../ContextTypes/InputState.h"
#include "../ContextTypes/WindowDetails.h"
#include <unordered_map>
#include <string>
#include "imgui.h"

namespace Input
{
	static float speedModifier = 2.5f;


	void UpdateInputStates(Registry& registry, float dt)
	{
		static bool freeMouse = false;
		static bool rUp = false;
		auto& camera = registry.ctx<Camera>();
		auto& input = registry.ctx<InputStates>();
		

		const glm::vec3& angles = camera.m_EulerRots;
		dt /=1000.0f;

		//Update position
		{
			glm::vec3 ds{ 0.0f, 0.0f, 0.0f };
			//Do movement based on euler rots
			const float ang = glm::radians(angles.y);
			const float angLeft = glm::radians(angles.y + 90.0f);
			const float angRight = glm::radians(angles.y - 90.0f);

			if (input.W)
			{
				ds.x += std::sin(ang);
				ds.z -= std::cos(ang);
			}
			if (input.S)
			{
				ds.x -= std::sin(ang);
				ds.z += std::cos(ang);
			}
			if (input.D)
			{
				ds.x += std::sin(angLeft);
				ds.z -= std::cos(angLeft);
			}
			if (input.A)
			{
				ds.x += std::sin(angRight);
				ds.z -= std::cos(angRight);
			}
			if (input.SPACE)
			{
				ds.y += 0.5f;
			}
			if (input.Q)
			{
				ds.y -= 0.5f;
			}

			camera.MoveCamera(ds * dt * speedModifier);
		}


		//This is outside the if statement so that it doesn't rotate randomly after exiting
		Position& lastPos = input.lastPos;
		Position& currPos = input.currPos;
		//Rotate Camera
		if(!freeMouse)
		{

			double dy = currPos.x-lastPos.x; //Reason for this is that going left/right rotates ON y axis, similar for dx
			double dx = currPos.y - lastPos.y;
			lastPos = currPos;
			glm::vec3 dTheta{ dx, dy, 0 };
			
			//TODO: Create some sort of sensitivity.


			camera.RotateCamera(dTheta);
			
		}

		if (input.RButton && !rUp)
		{
			const WindowDetails& window = registry.ctx<WindowDetails>();
			ImGuiIO& io = ImGui::GetIO();
			if (freeMouse)
			{ //Mouse is interacting with game
				io.ConfigFlags = io.ConfigFlags | ImGuiConfigFlags_NoMouse; //disable imgui mouse interactions
				glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				glfwSetInputMode(window.window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
				input.MouseFree = false;
			}
			else
			{ //Mouse is freed to interact with imgui
				glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				glfwSetInputMode(window.window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
				glfwSetCursorPos(window.window, window.w / 2, window.h / 2);
				io.ConfigFlags = io.ConfigFlags & !ImGuiConfigFlags_NoMouse; //enable imgui mouse interaction
				//I could have ^ this but need to ensure that bit is definitely off.
				input.MouseFree = true;
			}
			freeMouse = !freeMouse;
			rUp = true;
		}
		else if (!input.RButton && rUp)
		{
			rUp = false;
		}

	}

	void InitInputSystem(Registry& registry)
	{
		SetRegistry(registry);
		SetKeyCallback(&KeyboardInput, registry);
		SetMouseButtonCallback(&MouseButtonInput, registry);
		SetMousePosCallback(&MousePosInput, registry);
		SetWindowResizeCallback(&WindowResizeInput, registry);
		SetMouseScrollCallback(&MouseScrollInput, registry);
		auto& pointerMap = registry.ctx<std::unordered_map<std::string, void*>>();
		pointerMap["speed"] = static_cast<void*>(&speedModifier);
	}

}