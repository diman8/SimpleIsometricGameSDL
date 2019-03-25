#include "Game.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include "MapRenderHelper.h"
#include "Patrol.h"
#include "Fireball.h"
#include "GunTower.h"

Game* Game::instance;

Game::Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		std::cout << "init error" << std::endl;
		exit(1);
	}
}

Game * Game::getGame()
{
	if (Game::instance == nullptr)
	{
		Game::instance = new Game();
	}
	return Game::instance;
}

int Game::loadImage(char * path)
{
	return 0;
}

int Game::init(char* title, int width, int height, int fps)
{
	window = SDL_CreateWindow(title,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, NULL);
	if (!window)
	{
		std::cout << "window error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		std::cout << "renderer error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(1);
	}
	SDL_SetRenderDrawColor(renderer, 150, 150, 255, 255);
	this->frameDelay = 1000 / fps;
	isRunning = true;

	win = new Sprite("imgs/win.png");
	lose = new Sprite("imgs/lose.png");
	
	start();

	//map = new Map();
	//pl = new Player(0, 0);

	//for (int x = 0; x < map->sizex; x++)
	//{
	//	for (int y = 0; y < map->sizey; y++)
	//	{
	//		arrGO.push_back((IGameObject*) new MapRenderHelper({ x,y }));
	//	}
	//}
	//arrGO.push_back(pl);


	//camera.offset_x = SCREEN_WIDTH_HALF;
	//camera.offset_y = SCREEN_HEIGHT_HALF;
}

void Game::reset()
{
	delete map;
	//delete pl;
	for (IGameObject* go : arrGO)
		delete go;
	arrGO.clear();
	dynGO.clear();

	start();
}

void Game::start()
{
	map = new Map();
	pl = new Player(0, 0);
	dynGO.push_back(pl);
	dynGO.push_back(new Patrol({ 8,2 }, { 8,8 }));
	dynGO.push_back(new Patrol({ 0,12 }, { 8,10 }));
	dynGO.push_back(new Patrol({ 4,18 }, { 12,22 }));
	dynGO.push_back(new Patrol({ 19,12 }, { 26,17 }));
	dynGO.push_back(new GunTower({ 10,8 }, { -4.0f, 2.0f }));
	dynGO.push_back(new GunTower({ 14,12 }, { -4.0f, 2.0f },100));
	dynGO.push_back(new GunTower({ 19,20 }, { 4.0f, 2.0f }));
	dynGO.push_back(new GunTower({ 19,22 }, { 4.0f, 2.0f }, 140));

	for (int x = 0; x < map->sizex; x++)
	{
		for (int y = 0; y < map->sizey; y++)
		{
			arrGO.push_back((IGameObject*) new MapRenderHelper({ x,y }));
		}
	}

	for (IGameObject* go : dynGO)
	{
		arrGO.push_back(go);
	}

	splashScreen = SplashScreen::NONE;
	camera.offset_x = SCREEN_WIDTH_HALF;
	camera.offset_y = SCREEN_HEIGHT_HALF;
}

int Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				isRunning = false;
				break;
			case SDL_SCANCODE_TAB:
				if (splashScreen == SplashScreen::NONE) splashScreen = SplashScreen::WIN;
				else if (splashScreen == SplashScreen::WIN) splashScreen = SplashScreen::LOSE;
				else splashScreen = SplashScreen::NONE;
				break;
			case SDL_SCANCODE_R:
				reset();
				break;
			//case SDL_SCANCODE_W:
			//	camera.offset_y += 10;
			//	break;
			//case SDL_SCANCODE_A:
			//	camera.offset_x += 10;
			//	break;
			//case SDL_SCANCODE_S:
			//	camera.offset_y -= 10;
			//	break;
			//case SDL_SCANCODE_D:
			//	camera.offset_x -= 10;
			//	break;
			}
		case SDL_MOUSEBUTTONDOWN:
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int mx = event.button.x, my = event.button.y;
				SDL_Point p = Helper::Ort2Log(mx - camera.offset_x, my - camera.offset_y);
				//std::cout << "LMB_SCR: " << mx << " " << my << std::endl;
				//std::cout << "LMB_WOC: " << mx - camera.offset_x << " " << my - camera.offset_y << std::endl;
				//std::cout << "LMB_LOG: " << p.x << " " << p.y << std::endl;
				Game::getGame()->pl->moveToPoint(p);

			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				int mx = event.button.x, my = event.button.y;
				SDL_Point p = Helper::Ort2Log(mx - camera.offset_x, my - camera.offset_y);
				//std::cout << "RMB_SCR: " << mx << " " << my << std::endl;
				//std::cout << "RMB_WOC: " << mx - camera.offset_x << " " << my - camera.offset_y << std::endl;
				std::cout << "RMB_LOG: " << p.x << " " << p.y << std::endl;
				pl->stop();
				map->changeBlock(Helper::Ort2Log(mx - camera.offset_x, my - camera.offset_y));

			}
			break;
		}
		//case SDL_MOUSEWHEEL:
		//{
		//	if (event.wheel.y > 0) // scroll up
		//	{
		//		camera.zoom += 0.1;
		//	}
		//	else if (event.wheel.y < 0) // scroll down
		//	{
		//		camera.zoom -= 0.1;
		//	}
		//	break;
		//}
		default:
			break;
		}
	}


	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	if(keystates[SDL_SCANCODE_W]) camera.offset_y += 10;
	else if (keystates[SDL_SCANCODE_S]) camera.offset_y -= 10;
	if (keystates[SDL_SCANCODE_A]) camera.offset_x += 10;
	else if (keystates[SDL_SCANCODE_D]) camera.offset_x -= 10;

	return 0;
}

int Game::update()
{
	for (int i=0; i<dynGO.size();i++)
		dynGO[i]->update();
	//pl->update();
	SDL_Point pllog = pl->getLog();
	//fail check
	for (IGameObject* go : dynGO)
	{
		SDL_Point p = go->getLog();
		if (pllog.x == p.x && pllog.y == p.y && go->isDeadly())
		{
			splashScreen = SplashScreen::LOSE;
			break;
		}
	}
	//win check
	if ((pllog.x == 28) && (pllog.y == 28)) splashScreen = SplashScreen::WIN;

	//remove old GO
	for (IGameObject* go : arrGO2del)
	{
		dynGO.erase(std::remove(dynGO.begin(), dynGO.end(), go), dynGO.end());
		arrGO.erase(std::remove(arrGO.begin(), arrGO.end(), go), arrGO.end());
		delete go;
	}
	arrGO2del.clear();

	return 0;
}

//SDL_Point Game::myLog2Ort(int x, int y)
//{
//	SDL_Point p = Helper::Log2Ort(x, y);
//	p.x += -TILE_WIDTH_HALF + camera.offset_x;
//	p.y += -TILE_HEIGHT_HALF + camera.offset_y;
//	return p;
//}

//bool comparatorGO(const IGameObject* go1, const IGameObject* go2)
//{
//	if (go1->getZOrder() == go2->getZOrder()) return (go1->isTall());
//	else return go1->getZOrder() < go2->getZOrder();
//}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	// sort array
	std::sort(arrGO.begin(), arrGO.end(),
		[](const IGameObject* go1, const IGameObject* go2)
	{
		return go1->getZOrder() < go2->getZOrder();
	});
	//std::sort(arrGO.begin(), arrGO.end(), comparatorGO);
	// draw all GO
	for (IGameObject* go : arrGO)
	{
		go->render();
	}

	//screen
	if (splashScreen == SplashScreen::WIN) win->renderToScreen(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF);
	else if (splashScreen == SplashScreen::LOSE) lose->renderToScreen(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF);

	SDL_RenderPresent(renderer);
}

void Game::tick()
{
	tickStart = SDL_GetTicks();
}

void Game::tock()
{
	int time = SDL_GetTicks() - tickStart;
	if (time < frameDelay)
	{
		SDL_Delay(frameDelay - time);
	}
}

float* Game::getWeightedMap()
{
	int len = map->sizex * map->sizey;
	float inf = std::numeric_limits<float>::infinity();
	float *wmap = new float[len];
	for (int i = 0; i < len; i++) wmap[i] = 1;

	//map
	for (int i = 0; i < len; i++)
	{
		if (map->map[i] == (int)Tile::Stone)
		{
			wmap[i] = inf;
		}
	}

	//dyn
	for (IGameObject* go : dynGO)
	{
		if (!go->isDeadly() && (go != pl))
		{
			SDL_Point p = go->getLog();
			wmap[p.x + p.y*map->sizex] = inf;
		}
	}

	return wmap;
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::destroyAndExit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(1);
}

