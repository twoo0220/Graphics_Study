#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "RenderObject.h"

class Triangle : public RenderObject
{
public:
	Triangle();
	~Triangle() = default;

	void shaderCompile();
	void update();

private:
	const char* mVertexSource =
		"#version 330 core \n\
		in vec4 vertexPos; \n\
		void main(void) { \n\
			gl_Position = vertexPos; \n\
		}";
	const char* mFragSource =
		"#version 330 core \n\
		out vec4 FragColor; \n\
		void main(void) { \n\
			FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n\
		}";

	GLuint mProgram = 0;
	GLfloat mVertPos[16] = {
	-0.5F, -0.5F, 0.0F, 1.0F,
	+0.5F, -0.5F, 0.0F, 1.0F,
	-0.5F, +0.5F, 0.0F, 1.0F,
	};
};
