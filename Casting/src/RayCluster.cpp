#include "RayCluster.h"

void RayCluster::Initialize(int numWall, float rayPosX, float rayPosY)
{
	m_numWalls = numWall;

	Walls.push_back(new Wall(10, 10, 10, 950));
	Walls.push_back(new Wall(10, 10, 1270, 10));
	Walls.push_back(new Wall(1270, 10, 1270, 950));
	Walls.push_back(new Wall(10, 950, 1270, 950));

	for (int i = 0; i < m_numWalls - 4; i++) {
		Walls.push_back(new Wall((float)( rand() % 1280), (float) (rand() % 960), (float) (rand() % 1280), (float) (rand() % 960)));
	}

	for (float i = 0; i < 360; i += 1) {
		float x = 1 * sinf(i);
		float y = 1 * cosf(i);
		Rays.push_back(new Ray(rayPosX, rayPosY, x, y));
	}

	Distance = new float[m_numWalls];
	ReturnPoints = new Vector2D[m_numWalls];

	RayX = RayY = 0;
}

RayCluster::~RayCluster()
{
	for (size_t i = 0; i < Walls.size(); i++)
		delete Walls[i];
	delete[] Distance;
	delete[] ReturnPoints;
	for (size_t i = 0; i < Rays.size(); i++)
		delete Rays[i];
}

void RayCluster::update(SDL_Renderer* renderer)
{
	for (size_t i = 0; i < Walls.size(); i++) {
		Walls[i]->render(renderer);
	}
	for (size_t i = 0; i < Rays.size(); i++) {
		for (int j = 0; j < m_numWalls; j++)
			ReturnPoints[j] = Rays[i]->cast(*Walls[j]);
		float temp = 0;
		for (int j = 0; j < m_numWalls; j++) {
			Distance[j] = sqrtf(((ReturnPoints[j].x - RayX) * (ReturnPoints[j].x - RayX)) + ((ReturnPoints[j].y - RayY) * (ReturnPoints[j].y - RayY)));
			if (ReturnPoints[j].x > 0 && ReturnPoints[j].y > 0) {
				temp = Distance[j];
			}
		}
		for (int j = 0; j < m_numWalls; j++) {
			if (ReturnPoints[j].x > 0 && ReturnPoints[j].y > 0) {
				if (temp > Distance[j])
					temp = Distance[j];
			}
		}
		for (int j = 0; j < m_numWalls; j++) {
			if (temp == Distance[j]) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawLineF(renderer, RayX, RayY, ReturnPoints[j].x, ReturnPoints[j].y);
			}
		}
		Rays[i]->set_position(RayX, RayY);
	}
}