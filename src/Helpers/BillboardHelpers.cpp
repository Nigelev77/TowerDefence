#include "BillboardHelpers.h"

#include "../Components/Billboard.h"
#include "../Helpers/TextureHelpers.h"

#include "glad/glad.h"

static GLuint boardID = 0;

static const float billboardBuffer[12] =
{
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f
};

static const unsigned int billboardIndices[6] =
{
	0, 2, 1,
	0, 3, 2
};

void InitBillboard()
{
	glGenVertexArrays(1, &boardID);
	glBindVertexArray(boardID);

	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, billboardBuffer, GL_STATIC_DRAW);

	GLuint indicesID;
	glGenBuffers(1, &indicesID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, billboardIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void AttachBillboard(Registry& registry, entt::entity entity, glm::vec3 pos)
{
	registry.emplace<BillboardComponent>(entity, pos);
	
}

void AttachBillboard(Registry& registry, entt::entity entity, glm::vec3 pos, unsigned int textureID)
{
	registry.emplace<BillboardComponent>(entity, textureID, pos);
}

void AttachBillboard(Registry& registry, entt::entity entity, glm::vec3 pos, unsigned int textureID, float size)
{
	registry.emplace<BillboardComponent>(entity, textureID, pos, glm::vec2{ size, size });
}

glm::mat4 CalculateBillboardMatrix(Registry& registry, entt::entity entity)
{
	//TODO: Do model matrix here
	//May not be required however
	return glm::mat4();
}

unsigned int GetBoardID()
{
	return boardID;
}

unsigned int GetBoardVertex()
{
	return 6;
}

unsigned int GetHealthbarTex()
{
	return GetTextureInfo("healthbar");
}
