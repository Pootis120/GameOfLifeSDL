#pragma once
#include <SDL.h>
#include <iostream>
#include "Grid.h"

#define INIT_CHECK(statement, error) if (statement) {std::cout << error << std::endl;}

class Window 
{
//SDL members
private:
	Uint16 m_win_width = 400;
	Uint16 m_win_height = 400;

	SDL_Window* m_win;
	Uint32 m_flags_win = SDL_WINDOW_SHOWN;
	SDL_Renderer* m_rend;
	Uint32 m_flags_rend = SDL_RENDERER_ACCELERATED;

	SDL_Event m_event;
//Game Members
private:
	bool m_quitApp = false;
	int m_mouse_x, m_mouse_y;
public:
	Window();
	~Window();

	void Run();

	void Input(Grid& game);
	void Update(Grid& game);
	void Render(Grid& game);
};