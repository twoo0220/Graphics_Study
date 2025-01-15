#include "Triangle.h"

Triangle::Triangle()
{
	mShader.use();
}

void Triangle::update()
{
	GLuint loc = glGetAttribLocation(mShader.getmID(), "vertexPos");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, mVertPos);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glFinish();
}
