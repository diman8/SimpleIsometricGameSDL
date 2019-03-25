#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Camera.h"
#include "Helper.h"
#include "Player.h"
#include "Map.h"
#include "AGameObject.h"
#include <vector>
#include <memory>
#define TILE_WIDTH_HALF 50
#define TILE_HEIGHT_HALF 25
#define SCREEN_WIDTH_HALF 512
#define SCREEN_HEIGHT_HALF 384
#define WIDTH 1024
#define HEIGHT 768

class Game
{
private:
	int frameDelay;
	Uint32 tickStart;
	static Game* instance;
	SDL_Window *window;
	Game();
	~Game();
	void destroyAndExit();
public:
	Sprite *win, *lose;
	enum class SplashScreen {NONE, WIN, LOSE} splashScreen=SplashScreen::NONE;
	Player* pl;
	Map* map;
	std::vector<IGameObject*> arrGO;
	std::vector<IGameObject*> dynGO;
	std::vector<IGameObject*> arrGO2del;
	Camera camera;
	SDL_Renderer *renderer;
	bool isRunning;
	static Game* getGame();
	int loadImage(char* path);
	int init(char* title, int width, int height, int fps = 60);
	void reset();
	void start();
	int handleEvents();
	int update();
	//SDL_Point myLog2Ort(int x, int y);
	void render();
	void tick();
	void tock();
	float* getWeightedMap();
};

