#pragma once

#include "SDL.h"
#include "Components.h"
#include "TextureManager.h"

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
		position = &entity->GetComponent<PositionComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;

		destRect.w = destRect.h = 64;
	}

	void Update() override
	{
		destRect.x = position->X();
		destRect.y = position->Y();
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
};