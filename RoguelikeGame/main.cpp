#include "Game.h"
#undef main

Game* game = nullptr;

int main()
{
	game = new Game();

	game->Init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, false);

	while (game->Running())
	{
		game->HandleEvents();
		game->Update();
		game->Render();
	}

	game->Clean();
}
