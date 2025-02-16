#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "RenderObject.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class cube : public RenderObject
{
public:
	cube() = default;
	~cube() = default;

	void initialize() override;
	void deinitialize() override;
	void update() override;

private:
	Shader mShader{
		"./ShaderSrc/Cube/cube.vs",
		"./ShaderSrc/Cube/cube.fs"
	};

	GLuint mVAO = 0;
	GLuint mVBO = 0;
	glm::vec4 mVertCube[6] = {
		{ -0.5f, -0.5f, 0.5f, 1.0f }, { 1.0f, 0.3f, 0.3f, 1.0f },
		{ -0.5f, -0.5f, 0.5f, 1.0f }, { 1.0f, 0.3f, 0.3f, 1.0f },
		{ 0.5f, -0.5f, -0.5f, 1.0f }, { 1.0f, 0.3f, 0.3f, 1.0f }
	};

	float mTheta = 0.0f;

};
