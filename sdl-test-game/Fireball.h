#pragma once
#include "AGameObject.h"

class Fireball : public AGameObject
{
	Float2D delta;
	int timer=120;
	int pos_ind;
public:
	Fireball(SDL_Point pos, Float2D delta);
	virtual ~Fireball();

	// Inherited via AGameObject
	virtual bool isDeadly() const override;
	virtual void update() override;
};

