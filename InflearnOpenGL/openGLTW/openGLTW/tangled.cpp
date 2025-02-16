#include "tangled.h"

void tangled::initialize()
{

}

void tangled::deinitialize()
{
}

void tangled::update()
{
	mShader.use();

	// privted the vertex attributes
	GLuint locPos = glGetAttribLocation(mShader.getmID(), "aPos");
	glEnableVertexAttribArray(locPos);
	GLuint locColor = glGetUniformLocation(mShader.getmID(), "tangledColor");

	// red 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertRed[0]));
	glUniform4f(locColor, 1.0F, 0.3F, 0.3F, 1.0F); // (light) red
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// green 
	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertGreen[0]));
	glUniform4f(locColor, 0.3F, 1.0F, 0.3F, 1.0F); // (light) green
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// blue
	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertBlue[0]));
	glUniform4f(locColor, 0.3F, 0.3F, 1.0F, 1.0F); // (light) blue
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// yellow
	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertYellow[0]));
	glUniform4f(locColor, 1.0F, 1.0F, 0.3F, 1.0F); // (light) yellow
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
