#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.open(vertexPath);
	fShaderFile.open(fragmentPath);
	std::stringstream vShaderStream, fShaderStream;

	vShaderStream << vShaderFile.rdbuf();
	fShaderStream << fShaderFile.rdbuf();

	vShaderFile.close();
	fShaderFile.close();

	std::string vertexCode = vShaderStream.str();
	std::string fragmentCode = fShaderStream.str();

	mVertesSource = vertexCode.c_str();
	mFragSource = fragmentCode.c_str();
}

void Shader::use()
{
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1d(glGetUniformLocation(mID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) const
{
}

void Shader::setFloat(const std::string& name, float value) const
{
}

