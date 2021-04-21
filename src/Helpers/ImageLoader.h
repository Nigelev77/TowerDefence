#pragma once
#include <string>
#include "TextureHelpers.h"

struct ImageInfo
{
	int x, y, colorRes;
	void* buffer;
};

void LoadImage(const std::string& path, ImageInfo& info);
void TextureLoadInit();
void LoadTextures();
/**
*@note The contents of info will not be valid after call
*/
void FreeImage(ImageInfo& info);
