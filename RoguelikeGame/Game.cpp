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

bool Game::isRunning = false;

auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

const char* MAP_FILE = "Assets/terrain.png";

enum GroupLabels : size_t
{
	MAP,
	PLAYER,
	ENEMY,
	COLLIDER
};


auto& tiles(manager.GetGroup(GroupLabels::MAP));
auto& players(manager.GetGroup(GroupLabels::PLAYER));
auto& enemies(manager.GetGroup(GroupLabels::ENEMY));


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

	Map::LoadMap("Assets/map.map", 25, 20);


	player.AddComponent<TransformComponent>(4);
	player.AddComponent<SpriteComponent>("Assets/player_anim.png", true);
	player.AddComponent<KeyBoardController>();
	player.AddComponent<ColliderComponent>("Player");
	player.AddGroup(GroupLabels::PLAYER);
	
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

	Vector2 pVel = player.GetComponent<TransformComponent>().velocity;
	int pSpeed = player.GetComponent<TransformComponent>().speed;
	
	for (auto t : tiles)
	{
		t->GetComponent<TileComponent>().dectRect.x += -(pVel.x * pSpeed);
		t->GetComponent<TileComponent>().dectRect.y += -(pVel.y * pSpeed);
	}

}



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

void Game::AddTile(int srcX, int srcY, int xPos, int yPos)
{
	auto& tile(manager.AddEntity());
	tile.AddComponent<TileComponent>(MAP_FILE, srcX, srcY, xPos, yPos);
	tile.AddGroup(GroupLabels::MAP);
}