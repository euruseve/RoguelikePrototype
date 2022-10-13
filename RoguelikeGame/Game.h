#pragma once

#include "SDL.h"
#include "SDL_image.h"

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int xPos, int yPos, int wighth, int height, bool fullscreen);
	
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool Running() { return isRunning; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
private:
	int count = 0;
	bool isRunning;
	SDL_Window* window;
};

