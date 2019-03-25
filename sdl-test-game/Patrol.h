#pragma once
#include "AGameObject.h"
#define TICK_P 12

class Patrol :
	public AGameObject
{
	std::vector<SDL_Point> waypoints;
	std::vector<SDL_Point> track;
	Float2D delta;
	int timer;
	int pos_ind;
	int waypoit_pos_ind;
public:
	bool isMoving = false;
	Patrol(SDL_Point a, SDL_Point b);
	virtual ~Patrol();

	// Inherited via AGameObject
	virtual void render();
	virtual bool isDeadly() const override;
	virtual void update() override;
};

