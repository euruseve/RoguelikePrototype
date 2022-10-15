#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <vector>

class ColliderComponent;
class AssetManager;

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
	static SDL_Rect camera;

	static AssetManager* assets;
	static bool isRunning;

	enum GroupLabels : size_t
	{
		MAP,
		PLAYER,
		COLLIDER,
		PROJECTILE
	};

private:
	int count = 0;
	SDL_Window* window;
};

