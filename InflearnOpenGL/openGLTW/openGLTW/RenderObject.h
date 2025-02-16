#pragma once
#include "Shader.h"

class RenderObject
{
public:
	RenderObject() = default;
	virtual ~RenderObject() = default;
	virtual void update() = 0;
};
