#pragma once

#include "Components.h"
#include "Vector2.h"

class TransformComponent : public Component
{
public:
	Vector2 position;

	TransformComponent()
	{
		position.x = 0;
		position.y = 0;
	}

	TransformComponent(int x, int y)
	{
		position.x = x;
		position.y = y;
	}

	void Update() override
	{

	}

};
