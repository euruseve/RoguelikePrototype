#pragma once

#include "SDL.h"
#include "Components.h"

class SpriteComponent : public Component
{
public:

	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		SetTexture(path);
	}

	void SetTexture(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;

		destRect.w = destRect.h = 64;
	}

	void Update() override
	{
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
};