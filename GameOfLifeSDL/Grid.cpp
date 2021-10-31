#include "Grid.h"

Grid::Grid(Uint16 w, Uint16 h, Uint16 numT_w, Uint16 numT_h, Uint16 btwn_tile)
	: width(w), height(h), numTiles_w(numT_w), numTiles_h(numT_h), btwnTile(btwn_tile)
{
	Uint16 num_tiles = numT_h * numT_w;
	m_aliveTiles.reserve(num_tiles);
	m_aliveTiles.resize(num_tiles);

	m_grid.reserve(num_tiles);
	m_grid.resize(num_tiles);

	tileWidth = (w / numT_w) - btwn_tile;
	tileHeight = (h / numT_h) - btwn_tile;

	int c = 0;
	for (int i = 0; i < numT_h; i++) 
	{
		for (int s = 0; s < numT_w; s++) 
		{
			m_grid[c] = {(tileWidth + btwn_tile) * s, (tileHeight + btwn_tile) * i, tileWidth, tileHeight};
			c++;
		}
	}
}
Grid::~Grid() {}

void Grid::DrawGrid(SDL_Renderer* rend) 
{
	for (int i = 0; i < m_grid.size(); i++)
	{
		switch(m_aliveTiles[i]) 
		{
		case true:
			SDL_SetRenderDrawColor(rend, aliver, aliveg, aliveb, 0xFF);
			break;
		//false
		default:
			SDL_SetRenderDrawColor(rend, deadr, deadg, deadb, 0xFF);
			break;
		}
		SDL_RenderFillRect(rend, &(m_grid[i]));
	}
}

//sigma function, I love it
void Grid::ProccessClick(int in_x, int in_y)
{
	//get index of blob of tile with empty space
	int numTileX_1 = in_x / (Grid::tileWidth + btwnTile);
	//return to the start of the blob subtract it from start position
	//to get position in blob
	int numTileX_2 = in_x - (numTileX_1 * (Grid::tileWidth + btwnTile));

	//same for y
	int numTileY_1 = in_y / (Grid::tileHeight + btwnTile);
	int numTileY_2 = in_y - (numTileY_1 * (Grid::tileHeight + btwnTile));

	//check if position of mouse is in tile area or blob area
	if (numTileX_2 > Grid::tileWidth || numTileY_2 > Grid::tileWidth) 
	{
		std::cout << "Space pressed" << std::endl;
		//break from function
		return;
	}
	//continue
	
	//index in array
	int index = (numTileY_1 * numTiles_w) + numTileX_1;

	//change state of tile after mouse press
	m_aliveTiles[index] = !m_aliveTiles[index];
	m_grid[index];
}