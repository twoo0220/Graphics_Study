#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "shaderClass.h"

class Texture
{
public:
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	void texUnit(Shader shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();

private:
	GLuint ID;
	GLenum type;
};