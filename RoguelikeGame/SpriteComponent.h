#pragma once

#include "SDL.h"
#include "Components.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>
#include "AssetManager.h"


class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	~SpriteComponent()
	{
	}

	SpriteComponent(std::string tId)
	{
		SetTexture(tId);
	}

	SpriteComponent(std::string tId, bool isAnimated)
	{
		animated = isAnimated;

		SetTexture(tId);

		Animation idle = Animation(0, 4, 800);
		Animation walk = Animation(1, 4, 200);
		Animation swalk = Animation(2, 4, 200);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);
		animations.emplace("SWalk", swalk);

		Play("Idle");
	}

	void SetTexture(std::string tId)
	{
		texture = Game::assets->GetTexture(tId);
	}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;

		srcRect.w = transform->width;
		srcRect.h = transform->height;

	}

	void Update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height; 

		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* aniName)
	{
		frames = animations[aniName].frames;
		animIndex = animations[aniName].index;
		speed = animations[aniName].speed;
	}

};