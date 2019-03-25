#include "Sprite.h"
#include "Helper.h"
#include "Game.h"


Sprite::~Sprite()
{
	SDL_DestroyTexture(tex);
}
void Sprite::renderToScreen(int posx, int posy)
{
	Helper::RenderToScreen(Game::getGame()->renderer, tex, rect.x + posx - origin.x, rect.y + posy - origin.y, rect.w, rect.h);
}

void Sprite::render(int posx, int posy)
{
	Helper::Render(Game::getGame()->renderer, tex, rect.x + posx - origin.x, rect.y + posy - origin.y, rect.w, rect.h);
}

void Sprite::render(float posx, float posy)
{
	Helper::Render(Game::getGame()->renderer, tex, rect.x + posx - origin.x, rect.y + posy - origin.y, rect.w, rect.h);
}


Sprite::Sprite(char * path, int origin_x, int origin_y)
{
	tex = Helper::LoadTexture(path, rect);
	origin.x = origin_x;
	origin.y = origin_y;
}

Sprite::Sprite(char * path)
{
	tex = Helper::LoadTexture(path, rect);
	origin.x = rect.w / 2;
	origin.y = rect.h / 2;
}
