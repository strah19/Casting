#ifndef WALL
#define WALL

#include <SDL.h>
#include "Vector2D.h"

class Wall
{
public:
	Wall(float x1, float y1, float x2, float y2);
	void render(SDL_Renderer* renderer);
	void set_top_position(float x1, float y1, float x2 = -1, float y2 = -1)
	{
		a.x = x1;
		a.y = y1;
		if (x2 > -1 && y2 > -1) {
			b.x = x2;
			b.y = y2;
		}
	}
private:
	Vector2D a, b;
	friend class Ray;
};

#endif // !WALL