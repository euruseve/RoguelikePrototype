#pragma once

#include "Components.h"
#include "Vector2.h"

class TransformComponent : public Component
{
public:
	Vector2 position;
	Vector2 velocity;

	int speed = 3;

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

	void Init() override
	{
		velocity.x = 0;
		velocity.y = 0;
	}

	void Update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

};
