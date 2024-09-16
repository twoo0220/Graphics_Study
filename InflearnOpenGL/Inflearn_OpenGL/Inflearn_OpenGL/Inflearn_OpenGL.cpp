#include "Inflearn_OpenGL.h"
#include "GLFW/glfw3.h"

int main()
{
	std::cout << "Hello CMake.";

	GLFWwindow* window;

	if (!glfwInit())
	{
		std::cerr << "glfwInit Error";
		return -1;
	}

	window = glfwCreateWindow(640, 480, "twoo0220", NULL, NULL);
	if (window == nullptr)
	{
		glfwTerminate();
		std::cerr << "glfwCreatWindow failed\n";
		return -1;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
