#include "Wall.h"

Wall::Wall(float x1, float y1, float x2, float y2)
{
	a.x = x1;
	a.y = y1;
	b.x = x2;
	b.y = y2;
}

void Wall::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLineF(renderer, a.x, a.y, b.x, b.y);
}