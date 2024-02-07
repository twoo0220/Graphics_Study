#pragma once
#include "Actor.h"

class PacMan : public Actor
{
public:
	void Update(float deltaTime) override;
	void Draw() override;
};
