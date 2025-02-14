#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Triangle.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool initialize();
	void run();
	void update() {};

private:
	void calculateFPS();

	static void refreshFunc(GLFWwindow* window);
	static void keyFunc(GLFWwindow* window, int key, int scancode, int action, int mods);

	GLFWwindow* mWindow = nullptr;
	std::vector<std::shared_ptr<RenderObject>> mRenderObject;

	static float mColor[4];
};
