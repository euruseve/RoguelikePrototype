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


auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

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

	player.AddComponent<TransformComponent>(2);
	player.AddComponent<SpriteComponent>("Assets/player.png");
	player.AddComponent<KeyBoardController>();
	player.AddComponent<ColliderComponent>("Player");


	wall.AddComponent<TransformComponent>(300.f, 300.f, 300, 20, 1);
	wall.AddComponent<SpriteComponent>("Assets/wall.png");
	wall.AddComponent<ColliderComponent>("Wall");
	
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

	if (Collision::AABB(player.GetComponent<ColliderComponent>().collider,
						wall.GetComponent<ColliderComponent>().collider))
	{
		std::cout << "Collide" << std::endl;
	}

}

void Game::Render()
{
	SDL_RenderClear(renderer);

	map->DrawMap();
	manager.Draw();

	SDL_RenderPresent(renderer); 
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
