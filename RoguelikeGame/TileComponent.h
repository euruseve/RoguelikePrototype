#pragma once

#include "ECS.h"
#include "SDL.h"

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, dectRect;
	Vector2 position;

	TileComponent() = default;
	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(std::string tId, int srcX, int srcY, int x, int y, int tsize, int tscale)
	{
		texture = Game::assets->GetTexture(tId);

		position.x = x;
		position.y = y;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;

		dectRect.x = x;
		dectRect.y = y;
		dectRect.w = dectRect.h = tsize * tscale;
	}

	void Update() override
	{
		dectRect.x = position.x - Game::camera.x;
		dectRect.y = position.y - Game::camera.y;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, dectRect, SDL_FLIP_NONE);
	}

};