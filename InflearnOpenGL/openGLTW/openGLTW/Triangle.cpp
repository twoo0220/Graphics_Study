#include "Triangle.h"

void Triangle::update()
{
	mShader.use();

	GLuint loc = glGetAttribLocation(mShader.getmID(), "vertexPos");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, mVertPos);

	GLuint locMove = glGetUniformLocation(mShader.getmID(), "uTheta");
	glUniform1f(locMove, mTheta);
	mTheta += 0.01f;

	glDrawArrays(GL_TRIANGLES, 0, 3);
}
