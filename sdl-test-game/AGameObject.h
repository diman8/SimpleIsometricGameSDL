#pragma once

#include "IGameObject.h"
#include "Helper.h"
#include "Sprite.h"

class AGameObject : public IGameObject
{
protected:
	Sprite* sprt;
	Float2D pos;
public:
	SDL_Point logical;
	virtual void update()=0;
	virtual int getZOrder() const;
	virtual void render();
	virtual SDL_Point getLog();
	AGameObject();
	AGameObject(char * path, int origin_x, int origin_y);
	AGameObject(char * path);
	virtual ~AGameObject();
};

