#pragma once
#include "AGameObject.h"
#include <SDL.h>
#include <vector>
#define TICK 20

class Player : public AGameObject
{
	std::vector<SDL_Point> track;
	Float2D delta;
	int timer;
	int pos_ind;
public:
	//virtual int getZOrder() const;
	bool isMoving=false;
	void moveToPoint(SDL_Point p);
	void stop();
	Player(int x, int y);
	virtual void update();
	virtual void render();
	virtual ~Player();
	virtual bool isDeadly() const;
};

