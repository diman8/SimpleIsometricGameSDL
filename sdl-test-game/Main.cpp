#include <iostream>
#include "Game.h"


int main(int argc, char *argv[])
{
	Game* game_inst = Game::getGame();
	
	game_inst->init("Isometric test", WIDTH, HEIGHT);

	while (game_inst->isRunning)
	{
		game_inst->tick();
		game_inst->handleEvents();
		game_inst->update();
		game_inst->render();
		game_inst->tock();
	}
	return 0;
}