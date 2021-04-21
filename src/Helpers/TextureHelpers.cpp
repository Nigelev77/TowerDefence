#include "TextureHelpers.h"

#include <unordered_map> //Could be better to use a set or an array with an enum but good enough for now

static std::unordered_map<const char*, GLuint> textures{};


void StoreTextureInfo(GLuint texID, const char* texName)
{
	textures.emplace(std::make_pair(texName, texID));
}

GLuint GetTextureInfo(const char* texName)
{
	if (textures.contains(texName)) return textures[texName]; //Just in case, but can remove this and just return if certain
	return 0;
}