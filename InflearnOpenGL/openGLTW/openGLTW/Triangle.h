#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "RenderObject.h"

class Triangle : public RenderObject
{
public:
	Triangle();
	~Triangle() = default;

	void update();

private:
	Shader mShader{ "Triangle.vs", "Triangle.fs" };

	GLuint mProgram = 0;
	GLfloat mVertPos[16] = {
	-0.5F, -0.5F, 0.0F, 1.0F,
	+0.5F, -0.5F, 0.0F, 1.0F,
	-0.5F, +0.5F, 0.0F, 1.0F,
	};
};
