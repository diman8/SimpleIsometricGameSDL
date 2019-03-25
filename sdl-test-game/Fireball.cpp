#include "Fireball.h"
#include "Game.h"
#include "Helper.h"


Fireball::Fireball(SDL_Point lpos, Float2D delta) : AGameObject()
{
	if (delta.x < 0) sprt = new Sprite("imgs/fireball.png", TILE_WIDTH_HALF, 100);
	else sprt = new Sprite("imgs/fireball_flipped.png", TILE_WIDTH_HALF, 100);
	logical = lpos;
	SDL_Point p = Helper::Log2Ort(logical.x, logical.y);
	pos = { (float)p.x, (float)p.y };
	this->delta = delta;
}

Fireball::~Fireball()
{
}

bool Fireball::isDeadly() const
{
	return true;
}

void Fireball::update()
{
	if (--timer < 0)
	{
		Game::getGame()->arrGO2del.push_back(this);
	}
	pos = { pos.x + delta.x, pos.y + delta.y };
	logical = Helper::Ort2Log(pos.x, pos.y);
}
