#pragma once

typedef unsigned int GLuint;

void StoreTextureInfo(GLuint texID, const char* texName);
GLuint GetTextureInfo(const char* texName);