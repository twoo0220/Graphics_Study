#include "Triangle.h"

Triangle::Triangle()
{
}

void Triangle::update()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.5f, 0.0f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, 0.0f);
	glEnd();
}
