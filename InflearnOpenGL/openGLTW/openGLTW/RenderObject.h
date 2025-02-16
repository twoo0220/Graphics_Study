#pragma once
#include "Shader.h"

class RenderObject
{
public:
	RenderObject() = default;
	virtual ~RenderObject() = default;

	virtual void initialize() = 0;
	virtual void deinitialize() = 0;
	virtual void update() = 0;
};
