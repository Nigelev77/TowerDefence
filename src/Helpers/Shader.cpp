#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "ErrorLogging.h"

static bool CompileStatus(GLuint shader)
{
	GLint status;
	if (glGetShaderiv(shader, GL_COMPILE_STATUS, &status); !status)
	{
		char infoLog[1024];
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		//ERR_LOG("Could not compile shader with ID: " + std::to_string(shader));
		//ERR_LOG(infoLog);
		std::cout << infoLog << '\n';
	}
	return status;
}


static GLuint CompileShader(const std::string& vPath, const std::string& fPath)
{
	GLuint programID;
	GLuint vertexID;
	GLuint fragID;

	programID = glCreateProgram();

	{
		vertexID = glCreateShader(GL_VERTEX_SHADER);
		std::ifstream	vStream{ vPath.c_str(), std::ios::in };
		std::stringstream fileString;
		std::string line;
		while (!vStream.eof())
		{
			std::getline(vStream, line);
			fileString << line << '\n';
		}
		//const char* vStr = fileString.str().c_str();
		const std::string vString{ fileString.str() };
		const char* vStr = vString.c_str();

		glShaderSource(vertexID, 1, &vStr, NULL);
		glCompileShader(vertexID);
		if (!CompileStatus(vertexID)) std::cout << "Could not compile Shader";

	}

	{
		fragID = glCreateShader(GL_FRAGMENT_SHADER);
		std::ifstream fStream{ fPath.c_str(), std::ios::in };
		std::stringstream fileString;
		std::string line;
		while (!fStream.eof())
		{
			std::getline(fStream, line);
			fileString << line << '\n';
		}
		const std::string fString{ fileString.str() };
		const char* fStr = fString.c_str();
		glShaderSource(fragID, 1, &fStr, NULL);
		glCompileShader(fragID);
		if (!CompileStatus(fragID)) std::cout<<"Could not compile shader\n";
	}

	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragID);

	glLinkProgram(programID);

	return programID;
}

Shader::Shader(std::string vPath, std::string fPath)
	: m_ProgID{ CompileShader(vPath, fPath) }, m_UniformMap{}
{

}

Shader::Shader()
	:m_ProgID{0}, m_UniformMap{}
{}

void Shader::Use()
{
	glUseProgram(m_ProgID);
}

void Shader::SetMat4(const glm::mat4& mat, std::string_view name)
{
	//GLuint loc = m_UniformMap[name.data()];
	glUseProgram(m_ProgID);
	GLuint loc = glGetUniformLocation(m_ProgID, name.data());
	glUniformMatrix4fv(loc, 1, false, &mat[0][0]);
	
}

void Shader::SetFloat(float val, std::string_view name)
{
	glUseProgram(m_ProgID);
	GLuint loc = glGetUniformLocation(m_ProgID, name.data());
	glUniform1f(loc, val);
}

void Shader::RegisterMat4(std::string_view name)
{
	Use();
	m_UniformMap[name.data()] = glGetUniformLocation(m_ProgID, name.data());
}


