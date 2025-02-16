#include "Triangle.h"

void Triangle::initialize()
{
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);

	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertPos), mVertPos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Triangle::deinitialize()
{
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
}

void Triangle::update()
{
	mShader.use();

	//GLuint loc = glGetAttribLocation(mShader.getmID(), "vertexPos");
	//glEnableVertexAttribArray(loc);
	//glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, mVertPos);
	glBindVertexArray(mVAO);

	GLuint locMove = glGetUniformLocation(mShader.getmID(), "uTheta");
	glUniform1f(locMove, mTheta);
	mTheta += 0.01f;

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}
