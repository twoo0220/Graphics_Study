#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	glfwTerminate();
}

bool Renderer::initialize()
{
	if (!glfwInit())
	{
		std::cerr << "glfwInit failed\n";
		return false;
	}

	mWindow = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (mWindow == nullptr)
	{
		glfwTerminate();
		std::cerr << "glfwCreateWindow failed\n";
		return false;
	}

	glfwMakeContextCurrent(mWindow);
	return true;
}

void Renderer::run()
{
	while (!glfwWindowShouldClose(mWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.5f, 0.0f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, 0.0f);
		glEnd();

		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}
