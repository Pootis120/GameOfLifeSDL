#include "Grid.h"

Grid::Grid(Uint16 w, Uint16 h, Uint16 numT_w, Uint16 numT_h, Uint16 btwn_tile)
	: width(w), height(h), numTiles_w(numT_w), numTiles_h(numT_h), btwnTile(btwn_tile)
{
	m_aliveTiles.resize(numT_w);
	for (int i = 0; i < m_aliveTiles.size(); i++) 
	{
		m_aliveTiles[i].resize(numT_h);
	}
	m_grid.resize(numT_w * numT_h);

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
	for (int i = 0; i < m_aliveTiles.size(); i++)
	{
		for (int s = 0; s < m_aliveTiles[i].size(); s++) 
		{
			switch (m_aliveTiles[i][s])
			{
			case true:
				SDL_SetRenderDrawColor(rend, aliver, aliveg, aliveb, 0xFF);
				break;
				//false
			default:
				SDL_SetRenderDrawColor(rend, deadr, deadg, deadb, 0xFF);
				break;
			}
			SDL_RenderFillRect(rend, &(m_grid[(i * numTiles_w) + s]));
		}
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
	m_aliveTiles[numTileY_1][numTileX_1] = !m_aliveTiles[numTileY_1][numTileX_1];
}

int Grid::CountNeighbours(int x, int y) 
{
	int num_neighb = 0;
	for (int j = -1; j <= 1; j++)
	{
		for (int k = -1; k <= 1; k++)
		{
			if (y + j < 0 || y + j > numTiles_w - 1) 
			{
				continue;
			}
			if (x + k < 0 || x + k > numTiles_h - 1) 
			{
				continue;
			}
			num_neighb += m_aliveTiles[y + j][x + k];
		}
	}
	num_neighb -= m_aliveTiles[y][x];
	return num_neighb;
}

void Grid::RunGame() 
{
	int count = 0;
	bool shouldBeDead = false;
	//this isn't efficient but it doesn't affect performance that much
	for (int i = 0; i < m_aliveTiles.size(); i++) 
	{
		for (int s = 0; s < m_aliveTiles[i].size(); s++) 
		{
			count = CountNeighbours(s, i);
			shouldBeDead = count < 2 || count > 5;
			if (m_aliveTiles[i][s] && shouldBeDead) 
			{
				m_aliveTiles[i][s] = false;
			}
			else if (!m_aliveTiles[i][s] && !shouldBeDead) 
			{
				m_aliveTiles[i][s] = true;
			}
		}
	}
}

void Grid::ChangeGrid() 
{

}