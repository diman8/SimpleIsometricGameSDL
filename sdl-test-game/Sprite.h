#pragma once
//#include "Game.h"
#include <SDL.h>

class Sprite
{
public:
	SDL_Texture *tex;
	SDL_Point origin;
	SDL_Rect rect;
	Sprite(char* path, int origin_x, int origin_y);
	Sprite(char * path);
	void render(int posx, int posy);
	void render(float posx, float posy);
	~Sprite();
	void renderToScreen(int posx, int posy);
};

