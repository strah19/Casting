#include <iostream>
#include <string>
#include "RayCluster.h"
#include <SDL.h>
#include <cmath>
#include <ctime>

SDL_Renderer* Renderer;
SDL_Window* Window;
SDL_Event Event;

int WallSize = 15;

RayCluster cluster;

bool LeftClickFlag = false;
int PreXPosition = 200, PreYPosition = 0;
std::string KeyInput;
std::string NumberKeys[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

bool init_sdl(std::string title, int width, int height, bool full)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failure in loading SDL" << std::endl;
		SDL_Quit();
		return false;
	}
	else {
		int flag = 0;
		if (full)
			flag = SDL_WINDOW_FULLSCREEN;

		Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flag);
		Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (Renderer == NULL || Window == NULL)
		{
			std::cout << "Failure in loading window" << std::endl;
			SDL_Quit();
			return false;
		}

		cluster.Initialize(WallSize, 200, 200);
	}
	return true;
}

void clean_up()
{
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);

	SDL_Quit();
}

bool event_loop()
{
	while (SDL_PollEvent(&Event))
	{
		switch (Event.type)
		{
		case SDL_QUIT:
		{
			return false;
			break;
		}
		case SDL_KEYDOWN:
		{
			switch (Event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
			{
				return false;
				break;
			}
			}
			KeyInput = SDL_GetKeyName(Event.key.keysym.sym);
			std::cout << "Key Hit: " << KeyInput << " At: " << Event.key.timestamp << std::endl;
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			switch (Event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{
				LeftClickFlag = true;
				break;
			}
			case SDL_BUTTON_RIGHT:
			{
				LeftClickFlag = false;
				break;
			}
			default:
				break;
			}
		}
		}
	}

	if (!LeftClickFlag) {
		PreXPosition = Event.button.x;
		PreYPosition = Event.button.y;
	}

	return true;
}

void update()
{
	if (LeftClickFlag) {
		for (int i = 0; i < 10; i++) {
			if (KeyInput == NumberKeys[i]) {
				cluster.set_wall_position(i, (float)Event.button.x, (float)Event.button.y);
			}
		}
		if (KeyInput == "C") {
			for (static int i = 0; i < WallSize; i++) {
				cluster.set_wall_position(i, 0.0f, 0.0f, 0.0f, 0.0f);
			}
		}
	}
}

void draw()
{
	SDL_SetRenderDrawColor(Renderer, 100, 100, 100, 100);
	SDL_RenderClear(Renderer);

	cluster.update(Renderer);
	cluster.position((float)PreXPosition, (float)PreYPosition);

	SDL_RenderPresent(Renderer);
}

int main(int argc, char* argv[])
{
	srand(unsigned int(NULL)); 
	init_sdl("Ray Casting", 1280, 960, false);
	bool Running = true;

	while (Running)
	{
		Running = event_loop();
		draw();
		update();
	}

	clean_up();
	return 0;
}