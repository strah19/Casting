#ifndef RAY
#define RAY

#include <SDL.h>
#include "Vector2D.h"
#include "Wall.h"

class Ray
{
public:
	Ray(float x, float y, float dx, float dy);
	void render(SDL_Renderer* renderer);
	void set_position(float x, float y) { pos.x = x; pos.y = y; }
	Vector2D cast(Wall wall);
private:
	Vector2D pos;
	Vector2D dir;
};

#endif // !RAY