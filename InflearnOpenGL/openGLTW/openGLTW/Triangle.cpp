#include "Triangle.h"

Triangle::Triangle()
{
	shaderCompile();
}

void Triangle::shaderCompile()
{
	GLuint vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &mVertexSource, nullptr);
	glCompileShader(vert);

	GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &mFragSource, nullptr);
	glCompileShader(frag);

	mProgram = glCreateProgram();
	glAttachShader(mProgram, vert);
	glAttachShader(mProgram, frag);
	glLinkProgram(mProgram);

	glUseProgram(mProgram);
}

void Triangle::update()
{
	glClear(GL_COLOR_BUFFER_BIT);
	GLuint loc = glGetAttribLocation(mProgram, "vertexPos");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, mVertPos);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glFinish();
}
