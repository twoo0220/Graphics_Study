#pragma once
#include <iostream>
#include <vector>
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
	static void refreshFunc(GLFWwindow* window);
	static void keyFunc(GLFWwindow* window, int key, int scancode, int action, int mods);

	GLFWwindow* mWindow = nullptr;
	std::vector<std::shared_ptr<RenderObject>> mRenderObject;

	float mColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
};