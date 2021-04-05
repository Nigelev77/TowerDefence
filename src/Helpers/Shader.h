#pragma once
#include "glad/glad.h"
#include <string>
#include "glm/glm.hpp"
#include <unordered_map> //To store uniforms. Good enough for now

class Shader
{
public:
	Shader(std::string vPath, std::string fPath);
	Shader();
	void Use();


	GLuint m_ProgID;
	std::unordered_map<const char*, GLuint> m_UniformMap;


	void SetMat4(const glm::mat4& mat, std::string_view name);
	
	void SetFloat(float val, std::string_view name);
	void RegisterMat4(std::string_view name); //TO DO Check if this keeps creating new entries since string view could be deleted and thus invalid key
	



};

