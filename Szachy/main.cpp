#include <SDL.h>
#include <string>
#include "Board.cpp"

using namespace std;

int main(int argc, char **argv) {

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const int TILE_SIZE = 64;
	bool quit = false;
	
	SDL_Init(SDL_INIT_EVERYTHING); //za³¹czamy SDLa
	SDL_Window *window = SDL_CreateWindow("Szachy!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); //tworzy okno
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Event mainEvent;
	Board a(renderer);
	//Pawn pawn(renderer, 0, 0, PLAYER_1);

	while (!quit)
	{
		while (SDL_PollEvent(&mainEvent) != 0)
		{
			if (mainEvent.type == SDL_QUIT)
				quit = true;
		}

		SDL_RenderClear(renderer);
		a.render(renderer);
		//pawn.render(renderer);
		SDL_RenderPresent(renderer);
	}
	SDL_Quit();

	return 0;
}