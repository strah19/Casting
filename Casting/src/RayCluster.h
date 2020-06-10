#ifndef RAY_CLUSTER
#define RAYCLUSTER

#include <SDL.h>
#include "Ray.h"
#include <vector>
#include "Vector2D.h"

class RayCluster
{
public:
	RayCluster(int numWall, float rayPosX, float rayPosY);
	~RayCluster();
	void update(SDL_Renderer* renderer);
	inline void position(float x, float y) { RayX = x; RayY = y; }
	void set_wall_position(int index, float x1, float y1, float x2 = -1, float y2 = -1) { Walls[index]->set_top_position(x1, y1, x2, y2); }
private:
	std::vector<Ray*> Rays;
	std::vector<Wall*> Walls;
	Vector2D* ReturnPoints;
	float* Distance;
	int m_numWalls;
	float RayX, RayY;
};

#endif // !RAY_CLUSTER