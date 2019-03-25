#include "MapRenderHelper.h"
#include "Game.h"


void MapRenderHelper::update()
{
}

void MapRenderHelper::render()
{
	//SDL_Point p = Helper::Log2Ort(logical.x, logical.y);
	//(Game::getGame()->map->tiles.at((Tile)Game::getGame()->map->map[logical.x + logical.y*Game::getGame()->map->sizex]))->render(p.x, p.y);
	//SDL_Point l = Helper::Ort2Log(world.x, world.y);
	(Game::getGame()->map->tiles.at((Tile)Game::getGame()->map->map[logical.x + logical.y*Game::getGame()->map->sizex]))->render(world.x, world.y);
}

int MapRenderHelper::getZOrder() const
{
	//return logical.x + logical.y;
	return world.y;
}

bool MapRenderHelper::isDeadly() const
{
	return false;
}

SDL_Point MapRenderHelper::getLog()
{
	return logical;
}


MapRenderHelper::MapRenderHelper(SDL_Point p)
{
	logical = p;
	world = Helper::Log2Ort(logical.x, logical.y);
}


MapRenderHelper::~MapRenderHelper()
{
}
