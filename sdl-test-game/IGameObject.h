#pragma once
#include <SDL.h>

class IGameObject
{

public:
	virtual void update()=0;
	virtual void render()=0;
	virtual int getZOrder() const  = 0;
	virtual bool isDeadly() const = 0;
	virtual SDL_Point getLog() =0;
	virtual ~IGameObject();
};

