#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define GLM_FORCE_SWIZZLE
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "RenderObject.h"

class tangled : public RenderObject
{
public:
	tangled() = default;
	~tangled() = default;

	void initialize() override;
	void deinitialize() override;
	void update() override;
	
private:
	Shader mShader{ "./ShaderSrc/tangled/32-single-color.vert", "./ShaderSrc/tangled/32-single-color.frag" };

	GLuint mProgram = 0;
	glm::vec4 vertRed[6] = {
		{ +0.4F, -0.8F, -0.5F, 1.0F, },
		{ +0.6F, -0.8F, -0.5F, 1.0F, },
		{ +0.6F, +0.8F, +0.5F, 1.0F, },
		{ +0.6F, +0.8F, +0.5F, 1.0F, },
		{ +0.4F, +0.8F, +0.5F, 1.0F, },
		{ +0.4F, -0.8F, -0.5F, 1.0F, }
	};

	glm::vec4 vertGreen[6] = {
		{ +0.8F, +0.4F, -0.5F, 1.0f, },
		{ +0.8F, +0.6F, -0.5F, 1.0f, },
		{ -0.8F, +0.6F, +0.5F, 1.0f, },
		{ -0.8F, +0.6F, +0.5F, 1.0f, },
		{ -0.8F, +0.4F, +0.5F, 1.0f, },
		{ +0.8F, +0.4F, -0.5F, 1.0f, },
	};

	glm::vec4 vertBlue[6] = {
		{ -0.4F, +0.8F, -0.5F, 1.0F, },
		{ -0.6F, +0.8F, -0.5F, 1.0F, },
		{ -0.6F, -0.8F, +0.5F, 1.0F, },
		{ -0.6F, -0.8F, +0.5F, 1.0F, },
		{ -0.4F, -0.8F, +0.5F, 1.0F, },
		{ -0.4F, +0.8F, -0.5F, 1.0F, },
	};

	glm::vec4 vertYellow[6] = {
		{ -0.8F, -0.4F, -0.5F, 1.0f, },
		{ -0.8F, -0.6F, -0.5F, 1.0f, },
		{ +0.8F, -0.6F, +0.5F, 1.0f, },
		{ +0.8F, -0.6F, +0.5F, 1.0f, },
		{ +0.8F, -0.4F, +0.5F, 1.0f, },
		{ -0.8F, -0.4F, -0.5F, 1.0f, },
	};

};
