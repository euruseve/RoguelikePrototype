#pragma once

#include "ECS.h"
#include "Components.h"	
#include "Vector2.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int rng, int speed, Vector2 vel) : range(rng), speed(speed), velocity(vel)
	{}
	~ProjectileComponent(){}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void Update() override
	{
		distance += speed;

		if (distance > range)
		{
			entity->Destroy();
		}
		else if (transform->position.x > Game::camera.x + Game::camera.w ||
				transform->position.x < Game::camera.x ||
				transform->position.y > Game::camera.y + Game::camera.h ||
				transform->position.y < Game::camera.y)
		{
			entity->Destroy();
		}
	}

private:
	TransformComponent* transform;
	Vector2 velocity;

	int range = 0;
	int speed = 0;
	int distance = 0;
};