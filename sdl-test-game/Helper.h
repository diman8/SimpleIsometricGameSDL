#pragma once
#include <SDL.h>
#include "Camera.h"
#include <vector>

struct Float2D
{
	float x;
	float y;
};

namespace Helper
{
	bool FindPath(const float* weights, const int w, const int h, SDL_Point start, SDL_Point goal, std::vector<SDL_Point> &path);
	//bool astar(
	//	const float* weights, const int h, const int w,
	//	const int start, const int goal, bool diag_ok,
	//	int* paths);
	SDL_Point Log2Ort(int x, int y);
	SDL_Point Ort2Log(float x, float y);
	SDL_Texture* LoadTexture(char * path, SDL_Rect & rect);
	void RenderToScreen(SDL_Renderer * renderer, SDL_Texture * texture, const int x, const int y, const int w, const int h);
	void Render(SDL_Renderer * renderer, SDL_Texture * texture, const int x, const int y, const int w, const int h, Camera * cam = nullptr);
	void Render(SDL_Renderer * renderer, SDL_Texture * texture, const SDL_Rect * dstrect, Camera * cam = nullptr);
};

