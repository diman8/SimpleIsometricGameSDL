#include "Patrol.h"
#include <cmath>
#include <iostream>
#include "Map.h"
#include "Game.h"

Patrol::Patrol(SDL_Point a, SDL_Point b) : AGameObject("imgs/guard.png", 45, 132)
{
	waypoints.push_back(a);
	waypoints.push_back(b);
	this->logical = { a.x,a.y };
	SDL_Point p = Helper::Log2Ort(a.x, a.y);
	this->pos = { (float)p.x, (float)p.y };
	
	waypoit_pos_ind = 0;
}

void Patrol::update()
{
	if (isMoving)
	{
		if (timer % TICK_P == 0)
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
				delta = { (float)(p1.x - p.x) / TICK_P, (float)(p1.y - p.y) / TICK_P };
				pos_ind = next_pos_ind;
			}
		}
		else
		{
			pos.x += delta.x;
			pos.y += delta.y;
		}
		timer = (timer + 1) % TICK_P;
	}
	else
	{
		track.clear();
		float* map1 = Game::getGame()->getWeightedMap();
		bool res = Helper::FindPath(map1, 30, 30, logical, waypoints[(waypoit_pos_ind++ % waypoints.size())], track);
		if (!res) return;
		pos_ind = 0;
		timer = 0;
		isMoving = true;
		delete map1;
	}
}

void Patrol::render()
{
	AGameObject::render();
}


Patrol::~Patrol()
{
}

bool Patrol::isDeadly() const
{
	return true;
}

