#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "RenderObject.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Triangle : public RenderObject
{
public:
	Triangle() = default;
	~Triangle() = default;

	void initialize() override;
	void deinitialize() override;
	void update() override;

private:
	Shader mShader{
		"./ShaderSrc/Triangle/Triangle.vs",
		"./ShaderSrc/Triangle/Triangle.fs"
	};

	GLuint mVAO = 0;
	GLuint mVBO = 0;
	GLfloat mVertPos[16] = {
	-0.5F, -0.5F, 0.0F, 1.0F,
	+0.5F, -0.5F, 0.0F, 1.0F,
	-0.5F, +0.5F, 0.0F, 1.0F,
	};

	float mTheta = 0.0f;

};
