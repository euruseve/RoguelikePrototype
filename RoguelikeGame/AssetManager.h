#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2.h"
#include "ECS.h"
#include "SDL_ttf.h"

class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	void CreateProjectile(std::string id, Vector2 pos, Vector2 vel, int range, int speed);

	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

	void AddFont(std::string id, std::string, int fontSize);
	TTF_Font* GetFont(std::string id);

private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
};

