#pragma once
#include "IGameObject.h"
#include <SDL.h>
#include <map>
#include <vector>
#include "Sprite.h"

enum class Tile {Gray, Stone, Red, Flag};

class Map
{
public:
	std::map<Tile, Sprite*> tiles;
	int* map;
	int sizex, sizey;
	std::vector<IGameObject*> rendTargets;
	Map();
	void changeBlock(SDL_Point log);
	//void renderGO(std::vector<IGameObject> &arr);
	virtual ~Map();
};

