#include <iostream>

#include "Game.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "Map.h"
#include "Collision.h"

#include "Components.h"

Map* map;

Manager manager;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());


enum GroupLabels : size_t
{
	MAP,
	PLAYER,
	ENEMY,
	COLLIDER
};


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
	
	map = new Map();

	//

	Map::LoadMap("Assets/map_16x16.map", 16, 16);


	player.AddComponent<TransformComponent>(2);
	player.AddComponent<SpriteComponent>("Assets/player_anim.png", true);
	player.AddComponent<KeyBoardController>();
	player.AddComponent<ColliderComponent>("Player");
	player.AddGroup(GroupLabels::PLAYER);

	wall.AddComponent<TransformComponent>(300.f, 300.f, 300, 20, 1);
	wall.AddComponent<SpriteComponent>("Assets/wall.png");
	wall.AddComponent<ColliderComponent>("Wall");
	wall.AddGroup(GroupLabels::MAP);
	
}

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
	manager.Refresh();
	manager.Update();

	for (auto c : colliders)
	{
		Collision::AABB(player.GetComponent<ColliderComponent>(), *c);
	}
}

auto& tiles(manager.GetGroup(GroupLabels::MAP));
auto& players(manager.GetGroup(GroupLabels::PLAYER));
auto& enemies(manager.GetGroup(GroupLabels::ENEMY));

void Game::Render()
{
	SDL_RenderClear(renderer);

	for (auto& t : tiles)
	{
		t->Draw();
	}

	for (auto& p : players)
	{
		p->Draw();
	}

	for (auto& e : enemies)
	{
		e->Draw();
	}


	SDL_RenderPresent(renderer); 
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.AddEntity());
	tile.AddComponent<TileComponent>(x, y, 32, 32, id);
	tile.AddGroup(GroupLabels::MAP);
}
