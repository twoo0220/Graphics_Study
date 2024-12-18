#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "RenderObject.h"

class Triangle : public RenderObject
{
public:
	Triangle();
	~Triangle() = default;

	void update();
private:

};
