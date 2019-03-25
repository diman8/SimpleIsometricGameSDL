#include "AGameObject.h"
#include "Sprite.h"
#include "Helper.h"
#include "Game.h"

int AGameObject::getZOrder() const
{
	return pos.y + TILE_HEIGHT_HALF;
}

void AGameObject::render()
{
	//Helper::Render(Game::getGame()->renderer, tex, rect.x + pos.x - origin.x, rect.y + pos.y - origin.y, rect.w, rect.h);
	sprt->render(pos.x, pos.y);
}

SDL_Point AGameObject::getLog()
{
	return logical;
}

AGameObject::AGameObject()
{
	//sprt = new Sprite("imgs/placeholder_obj.png");
}

AGameObject::AGameObject(char* path, int origin_x, int origin_y)
{
	sprt = new Sprite(path, origin_x, origin_y);

}

AGameObject::AGameObject(char* path)
{
	sprt = new Sprite(path);
}


AGameObject::~AGameObject()
{
	delete sprt;
}
