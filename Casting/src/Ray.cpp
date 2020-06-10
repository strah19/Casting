#include "Ray.h"
#include <SDL.h>

#define SCALE 10

Ray::Ray(float x, float y, float dx, float dy)
{
	pos.x = x;
	pos.y = y;
	dir.x = dx;
	dir.y = dy;
}

void Ray::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLineF(renderer, pos.x, pos.y, pos.x + dir.x * SCALE, pos.y + dir.y * SCALE);
}

Vector2D Ray::cast(Wall wall)
{
	Vector2D vec;
	vec.x = vec.y = 0;
	float x1 = wall.a.x;
	float y1 = wall.a.y;
	float x2 = wall.b.x;
	float y2 = wall.b.y;

	float x3 = pos.x;
	float y3 = pos.y;
	float x4 = pos.x + dir.x;
	float y4 = pos.y + dir.y;

	float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (den == 0)
		return vec;
	float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
	float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

	if (t > 0 && t < 1 && u > 0) {
		vec.x = x1 + t * (x2 - x1);
		vec.y = y1 + t * (y2 - y1);
		return vec;
	}
	else
		return vec;
}