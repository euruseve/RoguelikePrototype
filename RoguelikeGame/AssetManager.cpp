#include "AssetManager.h"
#include "Components.h"


AssetManager::AssetManager(Manager* man) : manager(man) {}

AssetManager::~AssetManager() {}

void AssetManager::CreateProjectile(std::string id, Vector2 pos, Vector2 vel, int range, int speed)
{
	auto& projectile(manager->AddEntity());
	projectile.AddComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
	projectile.AddComponent<SpriteComponent>(id, false);
	projectile.AddComponent<ProjectileComponent>(range, speed, vel); 
	projectile.AddComponent<ColliderComponent>("projectile"); 
	projectile.AddGroup(Game::GroupLabels::PROJECTILE);

}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* AssetManager::GetFont(std::string id)
{
	return fonts[id];
}
