#pragma once

#include "ECS.h"
#include "SDL.h"

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, dectRect;

	TileComponent() = default;
	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(const char* path, int srcX, int srcY, int x, int y)
	{
		texture = TextureManager::LoadTexture(path);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 32;

		dectRect.x = x;
		dectRect.y = y;
		dectRect.w = dectRect.h = 64;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, dectRect, SDL_FLIP_NONE);
	}

};