#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SDL.h"

class TileComponent : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent *sprite;

	SDL_Rect tileRect;

	int tileId;
	const char* path;

	TileComponent() = default;
	~TileComponent(){}

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;

		tileRect.w = w;
		tileRect.h = h;

		tileId = id;

		switch (tileId)
		{
		case 0:
			path = "Assets/dirt.png";
			break;

		case 1:
			path = "Assets/grass.png";
			break;

		case 2:
			path = "Assets/water.png";
			break;

		default:
			break;
		}
	}

	void Init() override
	{
		entity->AddComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->GetComponent<TransformComponent>();

		entity->AddComponent<SpriteComponent>(path);
		sprite = &entity->GetComponent<SpriteComponent>();
	}
};