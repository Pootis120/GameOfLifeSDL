#pragma once
#include <vector>
#include <SDL.h>


#ifdef _DEBUG

#include <iostream>

#endif // DEBUG

class Grid 
{
private:

	//const Color dead;
	//const Color alive(0);

	const Uint8 deadr = 0;
	const Uint8 deadg = 0xFF;
	const Uint8 deadb = 0xFF;

	const Uint8 aliver = 0xFF;
	const Uint8 aliveg = 0xFF;
	const Uint8 aliveb = 0xFF;
	
public:
	//might change to heap arrays
	std::vector<std::vector<bool>> m_aliveTiles;
	std::vector<std::vector<bool>> m_aliveTiles2;
	std::vector<SDL_Rect> m_grid;

	//Generations activly changing
	bool m_isRunning = false;

	Uint16 width = 0;
	Uint16 height = 0;
	Uint16 numTiles_w = 0;
	Uint16 numTiles_h = 0;
	Uint16 tileWidth;
	Uint16 tileHeight;
	Uint16 btwnTile;

	Grid(Uint16 w, Uint16 h, Uint16 numT_w, Uint16 numT_h, Uint16 btwn_tile = 10);
	~Grid();

	//renders grid to screen
	void DrawGrid(SDL_Renderer* rend);

	//checks which tile was clicked and changes it's state
	void ProccessClick(int in_x, int in_y);

	//counts the neighbours of a tile
	int CountNeighbours(int x, int y);

	//runs simulation to figure out next generation grid
	void RunGame();

	//changes grid from origin to result (m_aliveTiles2 -> m_aliveTiles)
	void ChangeGrid();
};