#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2.h"
#include "ECS.h"

class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	void CreateProjectile(std::string id, Vector2 pos, Vector2 vel, int range, int speed);

	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

private:
	std::map<std::string, SDL_Texture*> textures;
	Manager* manager;
};

