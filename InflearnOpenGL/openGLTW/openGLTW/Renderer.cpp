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

	// Must be used after glfwMakeContextCurrent()
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "glewInit failed : " << glewGetErrorString(err) << "\n";
		return false;
	}

	glfwSetWindowRefreshCallback(mWindow, refreshFunc);
	glfwSetKeyCallback(mWindow, keyFunc);

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

void Renderer::refreshFunc(GLFWwindow* window)
{
	//std::cout << "Refresh CallBack!\n";
	// refresh
	glClear(GL_COLOR_BUFFER_BIT);
	glFinish();

	// GLFW action
	glfwSwapBuffers(window);
}

void Renderer::keyFunc(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
	{
		if (action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		break;
	}
	default:
	{
		break;
	}
	}
}
