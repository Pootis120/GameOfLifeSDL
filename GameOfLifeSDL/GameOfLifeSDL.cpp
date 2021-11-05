#include <iostream>
#include <SDL.h>
#include "Grid.h"

#define INIT_CHECK(statement, error) if (statement) {std::cout << error << std::endl; return 0;}

int main(int argc, char* args[])
{
	Uint16 win_width = 400;
	Uint16 win_height = 400;

	//Initialization ------------------------------------------------------------------------------------
	INIT_CHECK(SDL_Init(SDL_INIT_EVERYTHING) < 0, "Error: Could not load SDL");

	Uint32 flags_win = SDL_WINDOW_SHOWN;
	SDL_Window* win = SDL_CreateWindow("Hello World", 100, 100, win_width, win_height, flags_win);
	INIT_CHECK(win == NULL, "Error: Could not load window");

	Uint32 flags_rend = SDL_RENDERER_ACCELERATED;
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, flags_rend);
	INIT_CHECK(rend == NULL, "Error: Could not load Renderer");
	//---------------------------------------------------------------------------------------------------


	Grid grid(win_width, win_height, 5, 5, 10);
	bool quit = false;
	bool game_running = false;
	SDL_Event e;
	int mouse_x, mouse_y;
	while (!quit) 
	{
		while (SDL_PollEvent(&e) != 0) 
		{
			switch(e.type) 
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (e.button.button == SDL_BUTTON_LEFT && !game_running) 
				{
					SDL_GetMouseState(&mouse_x, &mouse_y);
					grid.ProccessClick(mouse_x, mouse_y);
				}
				else if (e.button.button == SDL_BUTTON_RIGHT) 
				{
					game_running = !game_running;
					std::cout << grid.CountNeighbours(1, 1) << std::endl;
					grid.RunGame();
				}
				break;
			default:
				break;
			}
		}
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
		SDL_RenderClear(rend);

		grid.DrawGrid(rend);

		SDL_RenderPresent(rend);
	}

	SDL_DestroyWindow(win);
	win = NULL;
	SDL_DestroyRenderer(rend);
	rend = NULL;

	SDL_Quit();

	return 0;
}