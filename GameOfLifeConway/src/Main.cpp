#include <iostream>
#include "Window.h"

int main(int argc, char** argv) 
{
	//Macro imported from Window header
	INIT_CHECK(SDL_Init(SDL_INIT_EVERYTHING) < 0, "Error: Could not load SDL");

	Window* window = new Window(/*params*/);
	window->Run();
	delete window;
	SDL_Quit();
	return 0;
}