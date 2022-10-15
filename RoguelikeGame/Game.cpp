#include <iostream>

#include "Game.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "Map.h"
#include "Collision.h"
#include "AssetManager.h"
#include "Components.h"

Map* map;

Manager manager;
SDL_Event Game::event;

SDL_Rect Game::camera{ 0, 0, 800, 640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.AddEntity());
auto& label(manager.AddEntity());

Game::Game(){}
Game::~Game(){}

SDL_Renderer* Game::renderer = nullptr;

void Game::Init(const char* title, int xPos, int yPos, int wighth, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, xPos, yPos, wighth, height, flags);
		
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	
	if (TTF_Init() == -1)
	{
		std::cerr << "TTF error" << std::endl;
	}

	assets->AddTexture("terrain", "Assets/terrain.png");
	assets->AddTexture("player", "Assets/player_anim.png");

	assets->AddTexture("projectile", "Assets/proj.png");

	assets->AddFont("arial", "Assets/arial.ttf", 32);

	//
	map = new Map("terrain", 2, 32);
	map->LoadMap("Assets/map.map", 25, 20);

	player.AddComponent<TransformComponent>(2);
	player.AddComponent<SpriteComponent>("player", true);
	player.AddComponent<KeyBoardController>();
	player.AddComponent<ColliderComponent>("Player");
	player.AddGroup(GroupLabels::PLAYER);
	
	SDL_Color color = { 255, 105, 180, 255 };
	label.AddComponent<UILabel>(30, 10, "I love Yana", "arial", color);


	assets->CreateProjectile("projectile", Vector2(600, 600), Vector2(2, 0), 200, 2);
}

auto& tiles(manager.GetGroup(Game::GroupLabels::MAP));
auto& colliders(manager.GetGroup(Game::GroupLabels::COLLIDER));
auto& players(manager.GetGroup(Game::GroupLabels::PLAYER));
auto& projectiles(manager.GetGroup(Game::GroupLabels::PROJECTILE));

void Game::HandleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::Update()
{
	SDL_Rect playerCol = player.GetComponent<ColliderComponent>().collider;
	Vector2 playerPos = player.GetComponent<TransformComponent>().position;

	manager.Refresh();
	manager.Update();

	for (auto& c : colliders)
	{ 
		SDL_Rect cCol = c->GetComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			player.GetComponent<TransformComponent>().position = playerPos;
		}
	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.GetComponent<ColliderComponent>().collider, p->GetComponent<ColliderComponent>().collider))
		{
			p->Destroy();
		}
	}

	camera.x = player.GetComponent<TransformComponent>().position.x - 400;
	camera.y = player.GetComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	for (auto& t : tiles)
	{
		t->Draw();
	}

	for (auto& c : colliders)
	{
		c->Draw();
	}

	for (auto& p : players)
	{
		p->Draw();
	}

	for (auto& p : projectiles)
	{
		p->Draw();
	}

	label.Draw();

	SDL_RenderPresent(renderer); 
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

