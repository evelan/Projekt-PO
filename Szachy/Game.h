#ifndef _Game_H_
#define _Game_H_
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Mouse.h"
#include "Board.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Texture.h"

/* "TRZYMA" ŚWIAT GRY I WSZYSTKIE OBIEKTY */

//tablica dynamicznee 
//przeciazenia operatorów
//polimorfizm

enum ENUM_PLAYER
{
	WHITE_PLAYER = 0,
	BLACK_PLAYER = 1
};

class Game
{
private:
	const int WINDOW_POS_X = 100;
	const int WINDOW_POS_Y = 100;
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	SDL_Renderer *renderer;
	SDL_Window *window;
	Texture background;

	DynamicObject *object[32]; // tablica ze wszystkimi figurami i ich podstawowymi funkcjami z DynamicObject

	Pawn pawn[16];
	Rook rook[4];
	Bishop bishop[4];
	Knight knight[4];
	King king[2];
	Queen queen[2];

	Mouse mouse;
	Board board;



	ENUM_PLAYER playerColor; // który gracz aktualnie wykonuje ruch

	int k = 0;
	int id; // wybrany pionek


private:
	void setFiguresDefault()
	{
		/* BIAŁE NA DOLE */
		for (int i = 0; i < 8; i++)
			pawn[i].set(renderer, i, 1, BLACK, board);

		for (int i = 0; i < 8; i++)
			pawn[i + 8].set(renderer, i, 6, WHITE, board);

		//wieża
		rook[0].set(renderer, 0, 0, BLACK, board);
		rook[1].set(renderer, 7, 0, BLACK, board);
		rook[2].set(renderer, 0, 7, WHITE, board);
		rook[3].set(renderer, 7, 7, WHITE, board);

		//goniec
		bishop[0].set(renderer, 1, 0, BLACK, board);
		bishop[1].set(renderer, 6, 0, BLACK, board);
		bishop[2].set(renderer, 1, 7, WHITE, board);
		bishop[3].set(renderer, 6, 7, WHITE, board);

		//koń
		knight[0].set(renderer, 2, 0, BLACK, board);
		knight[1].set(renderer, 5, 0, BLACK, board);
		knight[2].set(renderer, 2, 7, WHITE, board);
		knight[3].set(renderer, 5, 7, WHITE, board);

		//dama
		queen[0].set(renderer, 4, 0, BLACK, board);
		queen[1].set(renderer, 4, 7, WHITE, board);

		//król
		king[0].set(renderer, 3, 0, BLACK, board);
		king[1].set(renderer, 3, 7, WHITE, board);


		for (int i = 0; i < 32; i++)
		{
			if (i < 16)
				object[i] = &pawn[i];
			else if (i >= 16 && i < 20)
				object[i] = &bishop[i - 16];
			else if (i >= 20 && i < 24)
				object[i] = &rook[i - 20];
			else if (i >= 24 && i < 28)
				object[i] = &knight[i - 24];
			else if (i >= 28 && i < 30)
				object[i] = &queen[i - 28];
			else if (i >= 30 && i < 32)
				object[i] = &king[i - 30];
		}
	}

	void update()
	{
		/* RUCH GRACZA */
		//Gracz wybiera pionek
		if (mouse.bPressed())
		{
			//Sprawdzanie który pionek został wybrany
			for (int i = 0; i < 32; i++)
			{
				if (mouse.overlaps(object[i]->getX(), object[i]->getY()) && object[i]->getColor() == playerColor)
				{
					mouse.setFocus(); // myszka klikneła na pionek odpowiedniego dla gracza koloru
					id = i; 
					switch (object[i]->getFigure())
					{
					case PAWN:
						pawn[i].focus();
						break;

					case BISHOP:
						break;

					case ROOK:
						break;

					case KNIGHT:
						break;

					case QUEEN:
						break;

					case KING:
						break;
					}
					//break; //skoro już znalazło pionka to można przerwać pętlę, bo innego już nie znajdzie (nie powinno przynajmniej)
				}
			}
		}

		//Gracz porusza pionkiem
		if (mouse.bPressed() && mouse.isFocused())
		{
			for (int i = 0; i < 32; i++)
			{ 
				if ((mouse.overlaps(object[i]->getX(), object[i]->getY() + 1) ||
					mouse.overlaps(object[i]->getX(), object[i]->getY() - 1)) &&
					object[i]->getColor() == playerColor &&
					board.isFree(object[i]->getX(), (object[i]->getColor() == WHITE) ? object[i]->getY() - 1 : object[i]->getY() + 1)) 
				{	// czy myszka najechała na ZIELONE pole i czy ono jest WOLNE
						pawn[i].move();
						board.reset();
						mouse.resetFocus();

						/* ZAPIS RUCHU DO DYNAMICZNEJ TABLICY */

						changePlayer(); // zmiana gracza
						break;
				}
			}
		}

	}

	void render()
	{
		SDL_RenderClear(renderer);

		background.render();
		board.renderBoard();

		for (int i = 0; i < 32; i++)
			object[i]->render();

		SDL_RenderPresent(renderer);
	}

	void changePlayer()
	{
		playerColor = (playerColor == WHITE_PLAYER) ? BLACK_PLAYER : WHITE_PLAYER; // jeśli aktualnie jest biały to ustaw na czarnego, jesli czarny to na białego
	}

public:
	void start()
	{
		/* KONFIGURACJA SDL */
		SDL_Init(SDL_INIT_EVERYTHING); //załączamy SDLa
		window = SDL_CreateWindow("Szachy", WINDOW_POS_X, WINDOW_POS_Y, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); //tworzy okno
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //renderer

		/* KONFIGURACJA GRY */
		board.setup(renderer); //ustawiam obiekt szachownicy
		background.setup(renderer, "background.png", 0, 0, 800, 600); // ustawiam tło
		setFiguresDefault(); // ustawiamy figury na domyślne pozycje
		playerColor = WHITE_PLAYER;
	}

	void main()
	{
		while (mouse.quit())
		{
			update();
			render();
		}
	}


	void close()
	{
		SDL_Quit();
	}
};
#endif _Game_H_