#include "LoadingModel.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "ErrorLogging.h"

namespace Loader
{
	Assimp::Importer importer{};



	void LoadModel(Registry& registry, const std::string& path)
	{
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
		if (!scene)
		{
			ERR_LOG("Could not load file, file to load is: " + path);
			return;
		}

		

	}
}