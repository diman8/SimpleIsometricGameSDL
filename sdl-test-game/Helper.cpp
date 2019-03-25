#include "Game.h"
#include "Helper.h"
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm>


SDL_Point Helper::Log2Ort(int x, int y)
{
	SDL_Point p;
	//p.x = (x - y)* TILE_WIDTH_HALF;
	//p.y = (x + y)* TILE_HEIGHT_HALF;
	p.x = (x - y)* TILE_WIDTH_HALF;
	p.y = (x + y)* TILE_HEIGHT_HALF;
	return p;
}

SDL_Point Helper::Ort2Log(float x, float y)
{
	//SDL_Point p;
	//p.x = (x / TILE_WIDTH_HALF + y / TILE_HEIGHT_HALF) / 2;
	//p.y = (y / TILE_HEIGHT_HALF - x / TILE_WIDTH_HALF) / 2;
	float fx = (x / TILE_WIDTH_HALF + y / TILE_HEIGHT_HALF) / 2;
	float fy = (y / TILE_HEIGHT_HALF - x / TILE_WIDTH_HALF) / 2;
	return { (int)floor(fx), (int)floor(fy) };
}

SDL_Texture* Helper::LoadTexture(char * path, SDL_Rect & rect)
{
	SDL_Surface* srfc = IMG_Load(path);
	SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::getGame()->renderer, srfc);
	rect.x = 0;
	rect.y = 0;
	rect.w = srfc->w;
	rect.h = srfc->h;
	SDL_FreeSurface(srfc);
	return tex;
}

void Helper::RenderToScreen(SDL_Renderer * renderer, SDL_Texture * texture, const int x, const int y, const int w, const int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_RenderCopy(Game::getGame()->renderer, texture, NULL, &rect);
}

void Helper::Render(SDL_Renderer * renderer, SDL_Texture * texture, const int x, const int y, const int w, const int h, Camera * cam)
{
	if (!cam)
		cam = &(Game::getGame()->camera);
	SDL_Rect rect;
	rect.x = x + cam->offset_x;
	rect.y = y + cam->offset_y;
	rect.w = w*cam->zoom;
	rect.h = h*cam->zoom;
	SDL_RenderCopy(Game::getGame()->renderer, texture, NULL, &rect);
	//SDL_RenderDrawRect(Game::getGame()->renderer, &rect);
}

void Helper::Render(SDL_Renderer * renderer, SDL_Texture * texture, const SDL_Rect * dstrect, Camera * cam)
{
	Helper::Render(renderer, texture, dstrect->x, dstrect->y, dstrect->w, dstrect->h, cam);
}




// https://github.com/hjweide/a-star/blob/master/astar.cpp

// represents a single pixel
class Node {
public:
	int idx;     // index in the flattened grid
	float cost;  // cost of traversing this pixel

	Node(int i, float c) : idx(i), cost(c) {}
};

// the top of the priority queue is the greatest element by default,
// but we want the smallest, so flip the sign
bool operator<(const Node &n1, const Node &n2) {
	return n1.cost > n2.cost;
}

bool operator==(const Node &n1, const Node &n2) {
	return n1.idx == n2.idx;
}

// See for various grid heuristics:
// http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html#S7
// L_\inf norm (diagonal distance)
float linf_norm(int i0, int j0, int i1, int j1) {
	return std::max(std::abs(i0 - i1), std::abs(j0 - j1));
}

// L_1 norm (manhattan distance)
float l1_norm(int i0, int j0, int i1, int j1) {
	return std::abs(i0 - i1) + std::abs(j0 - j1);
}

// weights:        flattened h x w grid of costs
// h, w:           height and width of grid
// start, goal:    index of start/goal in flattened grid
// diag_ok:        if true, allows diagonal moves (8-conn.)
// paths (output): for each node, stores previous node in path
bool astar(
	const float* weights, const int h, const int w,
	const int start, const int goal, bool diag_ok,
	int* paths) {

	const float INF = std::numeric_limits<float>::infinity();

	Node start_node(start, 0.);
	Node goal_node(goal, 0.);

	float* costs = new float[h * w];
	for (int i = 0; i < h * w; ++i)
		costs[i] = INF;
	costs[start] = 0.;

	std::priority_queue<Node> nodes_to_visit;
	nodes_to_visit.push(start_node);

	int* nbrs = new int[8];

	bool solution_found = false;
	while (!nodes_to_visit.empty()) {
		// .top() doesn't actually remove the node
		Node cur = nodes_to_visit.top();

		if (cur == goal_node) {
			solution_found = true;
			break;
		}

		nodes_to_visit.pop();

		int row = cur.idx / w;
		int col = cur.idx % w;
		// check bounds and find up to eight neighbors: top to bottom, left to right
		nbrs[0] = (diag_ok && row > 0 && col > 0) ? cur.idx - w - 1 : -1;
		nbrs[1] = (row > 0) ? cur.idx - w : -1;
		nbrs[2] = (diag_ok && row > 0 && col + 1 < w) ? cur.idx - w + 1 : -1;
		nbrs[3] = (col > 0) ? cur.idx - 1 : -1;
		nbrs[4] = (col + 1 < w) ? cur.idx + 1 : -1;
		nbrs[5] = (diag_ok && row + 1 < h && col > 0) ? cur.idx + w - 1 : -1;
		nbrs[6] = (row + 1 < h) ? cur.idx + w : -1;
		nbrs[7] = (diag_ok && row + 1 < h && col + 1 < w) ? cur.idx + w + 1 : -1;

		float heuristic_cost;
		for (int i = 0; i < 8; ++i) {
			if (nbrs[i] >= 0) {
				// the sum of the cost so far and the cost of this move
				float new_cost = costs[cur.idx] + weights[nbrs[i]];
				if (new_cost < costs[nbrs[i]]) {
					// estimate the cost to the goal based on legal moves
					if (diag_ok) {
						heuristic_cost = linf_norm(nbrs[i] / w, nbrs[i] % w,
							goal / w, goal    % w);
					}
					else {
						heuristic_cost = l1_norm(nbrs[i] / w, nbrs[i] % w,
							goal / w, goal    % w);
					}

					// paths with lower expected cost are explored first
					float priority = new_cost + heuristic_cost;
					nodes_to_visit.push(Node(nbrs[i], priority));

					costs[nbrs[i]] = new_cost;
					paths[nbrs[i]] = cur.idx;
				}
			}
		}
	}

	delete[] costs;
	delete[] nbrs;

	return solution_found;
}


bool Helper::FindPath(const float * weights, const int w, const int h, SDL_Point start, SDL_Point goal, std::vector<SDL_Point> &path)
{
	int ipath[30 * 30];
	int start_ind = start.x + start.y*w;
	int goal_ind = goal.x + goal.y*w;
	bool res = astar(weights, h, w, start_ind, goal_ind, false, ipath);
	if (!((goal.x >= 0 && goal.x < w) &&
		(goal.y >= 0 && goal.y < h)))
		return false;
	if ((goal.x == start.x) && (goal.y == start.y))
		return false;

	if (res)
	{
		path.push_back(goal);
		int ind = goal_ind;
		while (ipath[ind] != start_ind)
		{
			int x = ipath[ind] % w;
			int y = ipath[ind] / w;
			path.push_back({ x,y });
			ind = ipath[ind];
		}
		path.push_back(start);
		std::reverse(path.begin(), path.end());
	}
	return res;
}