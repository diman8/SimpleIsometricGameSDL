#include "Player.h"
#include <cmath>
#include <iostream>
#include "Map.h"
#include "Game.h"

//int Player::getZOrder() const
//{
//	return logical.x + logical.y;
//}

void Player::moveToPoint(SDL_Point p)
{
	//std::cout << "Moving to (" << p.x << " " << p.y << ")" << std::endl;
	track.clear();
	isMoving = false;

	SDL_Point p1 = Helper::Log2Ort(this->logical.x, this->logical.y);
	this->pos = { (float)p1.x, (float)p1.y };

	float* map1 = Game::getGame()->getWeightedMap();
	if (map1[p.x + p.y*Game::getGame()->map->sizex] != 1)
	{
		std::cout << "Place is occupied" << std::endl;
		return;
	}
	bool res = Helper::FindPath(map1, 30, 30, this->logical, p, track);
	if (!res)
	{
		std::cout << "Place is unreacheble" << std::endl;
		return;
	}
	pos_ind = 0;
	timer = 0;
	isMoving = true;
	delete map1;
}

void Player::stop()
{
	SDL_Point p = Helper::Log2Ort(logical.x, logical.y);
	pos.x = p.x;
	pos.y = p.y;
	isMoving = false;
}

Player::Player(int x, int y) : AGameObject("imgs/player_c.png", 45, 132)
{
	this->logical = { x,y };
	SDL_Point p = Helper::Log2Ort(x, y);
	this->pos = { (float)p.x, (float)p.y };
}

void Player::update()
{
	if (isMoving)
	{
		if (timer % TICK == 0)
		{
			this->logical = { track[pos_ind].x, track[pos_ind].y };
			SDL_Point p = Helper::Log2Ort(track[pos_ind].x, track[pos_ind].y);
			pos.x = p.x;
			pos.y = p.y;
			//int next_pos_ind = (pos_ind + 1) % track.size();
			int next_pos_ind = (pos_ind + 1);
			if (next_pos_ind >= track.size())
			{
				isMoving = false;
			}
			else
			{
				SDL_Point p1 = Helper::Log2Ort(track[next_pos_ind].x, track[next_pos_ind].y);
				delta = { (float)(p1.x - p.x) / TICK, (float)(p1.y - p.y) / TICK };
				pos_ind = next_pos_ind;
			}
		}
		else
		{
			pos.x += delta.x;
			pos.y += delta.y;
		}
		timer = (timer + 1) % TICK;
	}
}

void Player::render()
{
	AGameObject::render();
}


Player::~Player()
{

}

bool Player::isDeadly() const
{
	return false;
}
