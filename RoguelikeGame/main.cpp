#include "Game.h"
#undef main

Game* game = nullptr;

int main()
{
	constexpr int FPS = 60;
	constexpr int FRAME_DELAY = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->Init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);

	while (game->Running())
	{
		frameStart = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (FRAME_DELAY > frameTime)
		{
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}

	game->Clean();
}
