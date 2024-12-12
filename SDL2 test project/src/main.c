#include <stdio.h>
#include <iso646.h>
#include <stdbool.h>
#include <SDL.h>

// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	//SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");

	SDL_Window* window = SDL_CreateWindow("SDL2 test project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	bool drawing = false;

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		SDL_Delay(10);
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				x1 = event.motion.x;
				y1 = event.motion.y;
				x2 = event.motion.x;
				y2 = event.motion.y;
				drawing = true;
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			if (drawing)
			{
				x2 = event.motion.x;
				y2 = event.motion.y;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				drawing = false;
				break;
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		// rendering code goes here

		if (drawing) {
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
		}

		// render window

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
