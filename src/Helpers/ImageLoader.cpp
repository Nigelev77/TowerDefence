#include "ImageLoader.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"

//TODO: Contemplate combining imageloader and texturehelper

void LoadImage(const std::string& path, ImageInfo& info)
{
	info.buffer = stbi_load(path.c_str(), &info.x, &info.y, &info.colorRes, info.colorRes);
}

void TextureLoadInit()
{
	stbi_set_flip_vertically_on_load(1);
}


void FreeImage(ImageInfo& info)
{
	if(info.buffer) stbi_image_free(info.buffer);
}

void LoadTextures()
{
	ImageInfo img;
	img.colorRes = 4;
	LoadImage("res/healthBar.png", img);
	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, img.x, img.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.buffer);


	StoreTextureInfo(texID, "healthbar");
	FreeImage(img);



}