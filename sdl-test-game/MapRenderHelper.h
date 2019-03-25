#pragma once
#include "SDL.h"
#include "IGameObject.h"
class MapRenderHelper : public IGameObject
{
	SDL_Point world;
	SDL_Point logical;
public:
	virtual void update();
	virtual void render();
	virtual int getZOrder() const;
	virtual bool isDeadly() const;
	virtual SDL_Point getLog();
	MapRenderHelper(SDL_Point p);
	virtual ~MapRenderHelper();
};

