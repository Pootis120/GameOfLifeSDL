#include "Window.h"

Window::Window() 
{
	//Initialization ------------------------------------------------------------------------------------
	m_win = SDL_CreateWindow("Hello World", 100, 100, m_win_width, m_win_height, m_flags_win);
	INIT_CHECK(m_win == NULL, "Error: Could not load window");

	m_rend = SDL_CreateRenderer(m_win, -1, m_flags_rend);
	INIT_CHECK(m_rend == NULL, "Error: Could not load Renderer");
	//---------------------------------------------------------------------------------------------------
}

Window::~Window() 
{
	SDL_DestroyRenderer(m_rend);
	m_rend = NULL;
	SDL_DestroyWindow(m_win);
	m_win = NULL;
}

void Window::Run() 
{
	Grid grid(m_win_width, m_win_height, 10, 10, 5);
	Uint32 frameStart;
	Uint16 frameTime;
	while(!m_quitApp) 
	{
		//Input
		
		Input(grid);
		//~Input
		Render(grid);

		
		//SDL_Delay(30);
	}
}

void Window::Input(Grid& game)
{
	while (SDL_PollEvent(&m_event) != 0)
	{
		switch (m_event.type)
		{
		case SDL_QUIT:
			m_quitApp = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (m_event.button.button == SDL_BUTTON_LEFT && !game.m_isRunning)
			{
				SDL_GetMouseState(&m_mouse_x, &m_mouse_y);
				game.ProccessClick(m_mouse_x, m_mouse_y);
			}
			else if (m_event.button.button == SDL_BUTTON_RIGHT)
			{

				game.m_isRunning = !game.m_isRunning;
				std::cout << game.CountNeighbours(3, 1) << std::endl;
				game.RunGame();
			}
			break;
		default:
			break;
		}
	}
}

void Window::Render(Grid& game) 
{
	//static Uint32 frameStart = SDL_GetTicks();
	SDL_SetRenderDrawColor(m_rend, 0, 0, 0, 0);
	SDL_RenderClear(m_rend);

	game.DrawGrid(m_rend);

	SDL_RenderPresent(m_rend);
	//Uint16 frameTime = SDL_GetTicks() - frameStart;
	//SDL_Delay(frameTime);
	SDL_Delay(30);
}