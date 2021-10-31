#pragma once
#include <vector>
#include <SDL.h>

#ifdef _DEBUG

#include <iostream>

#endif // DEBUG

class Grid 
{
private:
	const Uint8 deadr = 0;
	const Uint8 deadg = 0xFF;
	const Uint8 deadb = 0xFF;
public:
	//might change to heap arrays
	std::vector<bool> m_aliveTiles;
	std::vector<SDL_Rect> m_grid;

	const Uint8 aliver = 0xFF;
	const Uint8 aliveg = 0xFF;
	const Uint8 aliveb = 0xFF;

	Uint16 width = 0;
	Uint16 height = 0;
	Uint16 numTiles_w = 0;
	Uint16 numTiles_h = 0;
	Uint16 tileWidth;
	Uint16 tileHeight;
	Uint16 btwnTile;

	Grid(Uint16 w, Uint16 h, Uint16 numT_w, Uint16 numT_h, Uint16 btwn_tile = 10);
	~Grid();

	void DrawGrid(SDL_Renderer* rend);
	void ProccessClick(int in_x, int in_y);
};