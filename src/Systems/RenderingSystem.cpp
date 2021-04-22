#include "RenderingSystem.h"
#include "../ContextTypes/Camera.h"
#include "../Helpers/Shader.h"
#include "../Components/SimpleRender.h"
#include "../Components/Transform.h"
#include "../Components/Scale.h"
#include "../Components/LineStipRender.h"
#include "../Components/TransitionLine.h"
#include "../Components/Billboard.h"
#include "../Components/Health.h"

#include "../Helpers/LineTransformHelper.h"
#include "../Helpers/BillboardHelpers.h"
#include <iostream>
#include <unordered_map>
#include <string>

static std::unordered_map<std::string, Shader> shaderMap{};



static void RenderSimple(Registry& registry)
{
	if (registry.empty<SimpleRenderComponent>()) return;
	const Camera& cam = registry.ctx<Camera>();
	//Need to get a helper function or get some sort of system to enable shaders and get uniform variables etc
	Shader& defaultShader = registry.ctx<Shader>();
	defaultShader.Use();
	const glm::mat4 vp = cam.m_Proj * cam.m_viewMat;
	auto simpleEntities = registry.view<SimpleRenderComponent, TransformComponent, ScaleComponent>();
	for (auto entity : simpleEntities)
	{
		auto [render, transform, scale] = simpleEntities.get<SimpleRenderComponent, TransformComponent, ScaleComponent>(entity);
		const glm::mat4 transformMat = glm::scale(glm::translate(glm::mat4(1.0f), transform.pos), glm::vec3(scale.x, scale.y, scale.z));
		//This may have compiler warnings
		const glm::mat4 u_MVP = vp * transformMat;
		defaultShader.SetMat4(u_MVP, "u_MVP");
		glBindVertexArray(render.id);
		glDrawElements(GL_LINES, render.vertexCount, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}

}


static void RenderLines(Registry& registry)
{
	if (registry.empty<LineStripRenderComponent>()) return;
	const Camera& cam = registry.ctx<Camera>();
	Shader& defaultShader = registry.ctx<Shader>();
	defaultShader.Use();
	const glm::mat4 vp = cam.m_Proj * cam.m_viewMat;
	auto lines = registry.view<LineStripRenderComponent, TransformComponent>();
	for (auto entity : lines)
	{
		auto [render, transform] = registry.get<LineStripRenderComponent, TransformComponent>(entity);
		const glm::mat4 transformMat = glm::translate(glm::mat4(1.0f), transform.pos);
		const glm::mat4 u_MVP = vp * transformMat;
		defaultShader.SetMat4(u_MVP, "u_MVP");
		glBindVertexArray(render.id);
		glDrawElements(GL_LINE_STRIP, render.vertexCount, GL_UNSIGNED_INT, nullptr);
	}
	glBindVertexArray(0);
}

static void RenderTransitionLines(Registry& registry)
{
	auto lines = registry.view<TransitionLineComponent, TransformComponent>();

	const Camera& cam = registry.ctx<Camera>();
	Shader& defaultShader = registry.ctx<Shader>();
	defaultShader.Use();
	const glm::mat4 vp = cam.m_Proj * cam.m_viewMat;
	const static GLuint lineID = GetLineBuffer();
	const static unsigned int vertices = GetLineVertices();

	glLineWidth(5.0f);

	for (auto entity : lines)
	{
		auto [line, transform] = lines.get<TransitionLineComponent, TransformComponent>(entity);
		glm::mat4 transformMat = Line::GetTransformMatrix(line.line, transform.pos);
		const glm::mat4 u_MVP = vp * transformMat;
		defaultShader.SetMat4(u_MVP, "u_MVP");
		glBindVertexArray(lineID);
		glDrawElements(GL_LINES, vertices, GL_UNSIGNED_INT, nullptr);
	}

	glLineWidth(1.0f);

}

static void RenderBillboards(Registry& registry)
{
	static Shader& billShader = shaderMap["billboard"];
	const static GLuint boardID = GetBoardID();
	const static unsigned int boardVert = GetBoardVertex();
	Camera& cam = registry.ctx<Camera>();
	if (registry.empty<BillboardComponent>()) return;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_BLEND);
	billShader.Use();

	auto view = registry.view<BillboardComponent, TransformComponent, HealthComponent>();
	for (auto entity : view)
	{
		auto [bill, transform, health] = view.get<BillboardComponent, TransformComponent, HealthComponent>(entity);
		billShader.SetMat4(cam.GetViewMat(), "view");
		billShader.SetMat4(cam.m_Proj, "proj");
		billShader.SetFloat(health.health / health.maxHealth, "health");
		billShader.SetVec2(bill.size, "scale");
		billShader.SetVec3(transform.pos+bill.displacement, "worldPos");
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, bill.textureID);
		billShader.SetUInt1(0, "tex");
		glBindVertexArray(boardID);
		glDrawElements(GL_TRIANGLES, boardVert, GL_UNSIGNED_INT, nullptr);
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

void UpdateRendering(Registry& registry, float dt)
{
	//First clear main framebuffer
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	RenderSimple(registry);
	RenderLines(registry);
	RenderTransitionLines(registry);
	RenderBillboards(registry);
	Terrain::RenderTerrain(registry);

}

void InitRendering(Registry& registry)
{
	Terrain::InitTerrain(registry);

	//Load up Shaders
	shaderMap.emplace(std::make_pair("billboard", Shader{ "src/shaders/billboard.vert", "src/shaders/billboard.frag" }));
	Shader& billShader = shaderMap["billboard"]; //TODO: Instead of doing this, create the shader and then add it to the map
	billShader.Use();
	billShader.RegisterMat4("proj");
	billShader.RegisterMat4("view");
	billShader.RegisterUniform("worldPos");
	billShader.RegisterUniform("scale");
	billShader.RegisterUniform("health");
	billShader.RegisterUniform("tex");
	

}
