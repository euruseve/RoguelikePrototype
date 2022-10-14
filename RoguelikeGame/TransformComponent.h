#pragma once

#include "Components.h"
#include "Vector2.h"

class TransformComponent : public Component
{
public:
	Vector2 position;
	Vector2 velocity;

	int height = 32;
	int width = 32;

	int scale = 1;

	int speed = 3;

	TransformComponent()
	{
		position.x = 0;
		position.y = 0;
	}

	TransformComponent(int scale)
	{
		position.x = 0;
		position.y = 0;

		this->scale = scale;
	}


	TransformComponent(int x, int y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(int x, int y, int h, int w, int scale)
	{
		position.x = x;
		position.y = y;

		height = h;
		width = w;

		this->scale = scale;
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
