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
	GLFWwindow* mWindow = nullptr;
};