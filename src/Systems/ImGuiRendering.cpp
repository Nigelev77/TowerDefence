#include "ImGuiRendering.h"
#include "../ContextTypes/Camera.h"
#include <unordered_map>
#include <string>



void RenderImgui(Registry& registry, float dt)
{
#ifdef DEBUGGING_MODE
	const auto& pointerMap = registry.ctx<std::unordered_map<std::string, void*>>();
#endif
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow();
		ImGui::Begin("Hello World");

		Camera& cam = registry.ctx<Camera>();
		const glm::mat4& view = cam.GetViewMat();
		ImGui::DragFloat3("Camera Position: ", &cam.m_Pos.x);
		ImGui::DragFloat3("Camera Euler Rots: ", &cam.m_EulerRots.x);
		ImGui::DragFloat4("Camera View mat x", const_cast<float*>(&view[0].x));
		ImGui::DragFloat4("Camera View mat y", const_cast<float*>(&view[1].x));
		ImGui::DragFloat4("Camera View mat z", const_cast<float*>(&view[2].x));
		ImGui::DragFloat4("Camera View mat w", const_cast<float*>(&view[3].x));
		ImGui::Text("Frame Time: %d", dt);

#ifdef DEBUGGING_MODE
		ImGui::SliderFloat("Speed: ", (float*)pointerMap.at("speed"), 0.0f, 10.0f);
		ImGui::DragFloat("Enemy Speed: ", (float*)pointerMap.at("enemy_speed"));
#endif





		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
