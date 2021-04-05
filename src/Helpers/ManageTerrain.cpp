#include "ManageTerrain.h"
#include "glad/glad.h"
#include "ErrorLogging.h"
#include "Shader.h"
#include <string>
#include "../ContextTypes/Camera.h"

namespace Terrain
{

	extern float TowerBoundaries = 16.0f;

	struct RenderInfo
	{
		GLuint TerrainVAO;
		unsigned int vertexCount;
	};
	static RenderInfo TerrainVAO{};
	static GLuint TerrainIBO = 0;
	static GLuint TerrainVBO = 0;
	static std::string terrainVPath = "src/Shaders/terrain.vert";
	static std::string terrainFPath = "src/Shaders/terrain.frag";
	static Shader terrainShader;

	

	void CreateTerrain(Registry& registry)
	{
		glGenVertexArrays(1, &TerrainVAO.TerrainVAO);
		glBindVertexArray(TerrainVAO.TerrainVAO);

		float* verts = (float*)malloc(sizeof(float)*TERRAIN_SIZE*TERRAIN_SIZE*3);
		unsigned int* indices = (unsigned int*)malloc(sizeof(unsigned int) * TERRAIN_BOX_NUM * TERRAIN_BOX_NUM * 6);
		if (!(verts && indices))
		{
			ERR_LOG("Could not create terrain, malloc failed");
			return;
		}
		unsigned int ptr = 0;
		glGenBuffers(1, &TerrainVBO);
		for (int z = 0; z < TERRAIN_SIZE; z++)
		{
			for (int x = 0; x < TERRAIN_SIZE; x++)
			{
				verts[ptr++] = (float)x*TERRAIN_BOX_WIDTH;
				verts[ptr++] = 0;
				verts[ptr++] = -(float)z*TERRAIN_BOX_WIDTH;
			}
		}
		
		ptr = 0;

		//NEED TO DO INDICES
		glGenBuffers(1, &TerrainIBO);

		for (int z = 0; z < TERRAIN_BOX_NUM; z++)
		{
			for (int x = 0; x < TERRAIN_BOX_NUM; x++)
			{
				unsigned int bLeft = x+z*TERRAIN_SIZE;
				unsigned int bRight = bLeft + 1;
				unsigned int tLeft = x + (z + 1) * TERRAIN_SIZE;
				unsigned int tRight = tLeft + 1;
				indices[ptr++] = bLeft;
				indices[ptr++] = tLeft;
				indices[ptr++] = tRight;
				indices[ptr++] = bLeft;
				indices[ptr++] = tRight;
				indices[ptr++] = bRight;
			}
		}


		//NEED TO TAKE OUT PLAY AREA AND REPLACE WITH NEW OR DIFFERENT COLOUR
		//COULD BE DONE IN THE VAO INFO OR IN SHADER PROGRAMS


		glBindBuffer(GL_ARRAY_BUFFER, TerrainVBO);
		//NEED TO REMEMBER SIZE IS IN BYTES, USUALLY GLsizeiptr is requesting bytes
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * TERRAIN_SIZE * TERRAIN_SIZE * 3, verts, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, TerrainIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * TERRAIN_BOX_NUM * TERRAIN_BOX_NUM * 6, indices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

		TerrainVAO.vertexCount = TERRAIN_BOX_NUM * TERRAIN_BOX_NUM * 6;


		glBindVertexArray(0);

		terrainShader.RegisterMat4("u_MVP");
		terrainShader.RegisterMat4("boundary"); //TODO: Rename this to make it just register uniform

		free(verts);
		free(indices);

	}

	void RenderTerrain(Registry& registry)
	{
		Camera& cam = registry.ctx<Camera>();
		static glm::mat4 proj = cam.m_Proj;
		const glm::mat4& view = cam.CalculateViewMat();
		terrainShader.Use();
		const glm::mat4 u_MVP = proj*view;
		terrainShader.SetMat4(u_MVP, "u_MVP");
		terrainShader.SetFloat(Terrain::TowerBoundaries, "boundary");
		//TODO: Refactor and clean up externs and make a better way to implement these
		//constants that depend on values in the application in the shader code.
		
		glBindVertexArray(TerrainVAO.TerrainVAO);
		glDrawElements(GL_TRIANGLES, TerrainVAO.vertexCount, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}

	void InitTerrain(Registry& registry)
	{
		terrainShader = Shader{ terrainVPath, terrainFPath };
		CreateTerrain(registry);
	}
}