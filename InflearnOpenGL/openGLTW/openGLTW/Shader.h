#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "GL/glew.h"

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader() = default;

	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	
private:
	unsigned int mID = 0;
	const char* mVertesSource = nullptr;
	const char* mFragSource = nullptr;
};
