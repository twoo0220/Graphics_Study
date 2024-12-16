#pragma once
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool initialize();
	void run();

private:
	static void refreshFunc(GLFWwindow* window);
	static void keyFunc(GLFWwindow* window, int key, int scancode, int action, int mods);

	GLFWwindow* mWindow = nullptr;
};