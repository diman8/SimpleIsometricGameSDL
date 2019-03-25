#pragma once
#include "AGameObject.h"
#include "Helper.h"

class GunTower : public AGameObject
{
	int cyclerate;
	int timer=0;
	Float2D delta;
public:
	GunTower(SDL_Point lpos, Float2D delta, int cyclerate=180);
	virtual ~GunTower();

	// Inherited via AGameObject
	virtual bool isDeadly() const override;
	virtual void update() override;
};

