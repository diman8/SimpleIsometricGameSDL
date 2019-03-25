#include "GunTower.h"
#include "Fireball.h"
#include "Game.h"

GunTower::GunTower(SDL_Point lpos, Float2D delta, int cyclerate) : AGameObject()
{
	if (delta.x < 0) sprt = new Sprite("imgs/gun_tower.png", TILE_WIDTH_HALF, 100);
	else sprt = new Sprite("imgs/gun_tower_flipped.png", TILE_WIDTH_HALF, 100);
	logical = lpos;
	SDL_Point p = Helper::Log2Ort(logical.x, logical.y);
	pos = { (float)p.x, (float)p.y };
	this->delta = delta;
	this->cyclerate = cyclerate;
}

GunTower::~GunTower()
{
}

bool GunTower::isDeadly() const
{
	return false;
}

void GunTower::update()
{
	timer++;
	if ((timer % cyclerate) == 0)
	{
		auto ptr = new Fireball(logical, delta);
		Game::getGame()->dynGO.push_back(ptr);
		Game::getGame()->arrGO.push_back(ptr);
	}
}
