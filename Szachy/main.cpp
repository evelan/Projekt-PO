#include <SDL.h>
#include <string>
#include "Board.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"

using namespace std;

int main(int argc, char **argv) {

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const int TILE_SIZE = 64;
	const int POSITION_X = 100;
	const int POSITION_Y = 100;

	SDL_Init(SDL_INIT_EVERYTHING); //za³¹czamy SDLa
	SDL_Window *window = SDL_CreateWindow("Szachy!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); //tworzy okno
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //renderer
	SDL_Event mainEvent;

	Texture background(renderer, "background.png", 0, 0, 800, 600); // ustawiam t³o
	Board board(renderer); //tworzê obiekt szachownicy

	Pawn pawn[16];
	Rook rook[4];
	Bishop bishop[4];
	Knight knight[4];
	King king[2];
	Queen queen[2];

	for (int i = 0; i < 16; i++)
	{
		pawn[i].set(renderer, i, 1, BLACK);
		if (i > 7)
			pawn[i].set(renderer, i - 8, 6, WHITE);
	}

	//wie¿a
	rook[0].set(renderer, 0, 0, BLACK);
	rook[1].set(renderer, 7, 0, BLACK);
	rook[2].set(renderer, 0, 7, WHITE);
	rook[3].set(renderer, 7, 7, WHITE);

	//goniec
	bishop[0].set(renderer, 1, 0, BLACK);
	bishop[1].set(renderer, 6, 0, BLACK);
	bishop[2].set(renderer, 1, 7, WHITE);
	bishop[3].set(renderer, 6, 7, WHITE);

	//koñ
	knight[0].set(renderer, 2, 0, BLACK);
	knight[1].set(renderer, 5, 0, BLACK);
	knight[2].set(renderer, 2, 7, WHITE);
	knight[3].set(renderer, 5, 7, WHITE);

	//król
	king[0].set(renderer, 3, 0, BLACK);
	king[1].set(renderer, 3, 7, WHITE);

	//dama
	queen[0].set(renderer, 4, 0, BLACK);
	queen[1].set(renderer, 4, 7, WHITE);

	while ((SDL_PollEvent(&mainEvent) != 0) || (mainEvent.type != SDL_QUIT))
	{
		SDL_RenderClear(renderer);

		background.render(renderer);
		board.render(renderer);

		for (int i = 0; i < 16; i++)
			pawn[i].render(renderer);

		for (int i = 0; i < 4; i++)
		{
			rook[i].render(renderer);
			bishop[i].render(renderer);
			knight[i].render(renderer);
		}

		for (int i = 0; i < 2; i++)
		{
			queen[i].render(renderer);
			king[i].render(renderer);
		}

		SDL_RenderPresent(renderer);
	}
	SDL_Quit();

	return 0;
}