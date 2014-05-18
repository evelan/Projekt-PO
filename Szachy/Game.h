#ifndef _Game_H_
#define _Game_H_
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include "Text.h"
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

	ENUM_PLAYER playerColor; // który gracz aktualnie wykonuje ruch
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

	int k = 0;
	int id = -1; // numer pionka który został podświetlony przez gracza
	bool debug;

private:
	void setFiguresDefault() // ustawia pionki na domyślne pozycje
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
		queen[0].set(renderer, 3, 0, BLACK, board);
		queen[1].set(renderer, 3, 7, WHITE, board);

		//król
		king[0].set(renderer, 4, 0, BLACK, board);
		king[1].set(renderer, 4, 7, WHITE, board);


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

	void changePlayer()
	{
		playerColor = (playerColor == WHITE_PLAYER) ? BLACK_PLAYER : WHITE_PLAYER; // jeśli aktualnie jest biały to ustaw na czarnego, jesli czarny to na białego
	}

	void save() // zapisuje ruch pionka
	{

	}

	void open() //odtwarza ruch pionków
	{
		SDL_Delay(500);
	}

	void update()
	{
		if (mouse.kPressed(SDL_KEYUP))
			debug = true;
		if (mouse.kPressed(SDL_KEYDOWN))
			debug = false;

		/* RUCH GRACZA */
		// 1. Gracz wybiera pionek
		if (mouse.bPressed())
		{
			/* Sprawdzanie który pionek został wybrany */
			for (int i = 0; i < 32; i++)
			{
				//IF (myszka nachodzi na dany pionek, aktualny gracz wybiera pionek swojego koloru, pionek jest "żywy")
				if (mouse.overlaps(object[i]) && object[i]->getColor() == playerColor && object[i]->isAlive())
				{
					mouse.setFocus(); // informacja że myszka klikneła na pionek odpowiedniego koloru (tj. zaznaczyła go) 
					id = i; // numer pionka który został podświetlony przez gracza, dzieki temu przeunie sie wybrany przez nas pionek a nie jakiś inny, który spełni podobne warunki
					board.reset(); // resetuje całą tablicę domyślnych kolorów przed podświetlaniem ścieżki

					switch (object[i]->getFigure()) // sprawdzmy który pionek został klinięty aby podświetlić ściezkę dla danego typu pionka
					{
					case PAWN:
						pawn[i - PAWN].focus(); // podświetla jego ścieżkę
						break;

					case BISHOP:
						bishop[i - BISHOP].focus();
						break;

					case ROOK:
						rook[i - ROOK].focus();
						break;

					case KNIGHT:
						knight[i - KNIGHT].focus();
						break;

					case QUEEN:
						queen[i - QUEEN].focus();
						break;

					case KING:
						king[i - KING].focus();
						break;
					}
					break; // skoro już znalazło pionka to można przerwać pętlę, bo innego już nie znajdzie
				}
			}
		}

		// 2. Gracz porusza pionkiem
		if (mouse.bPressed() && mouse.isFocused()) // przycisk wciśnięty po wcześniejszym zaznaczeniu pionka
		{
			// Gracz przesuwa swój pionek
			if (board.isAllow(mouse.getX(), mouse.getY())) //sprawdzenie czy miejsce kliknięte jest dozwolone dla ruchu
			{
				object[id]->setPosition(mouse.getX(), mouse.getY()); // ustawiamy tam pionka

				if (object[id]->getFigure() == PAWN)
					pawn[id].moved();

				board.reset(); // resetujemy tablicę aby zlikwidować niepotrzebne już podświetleenia na planszy
				mouse.resetFocus(); // resetujemy zaznaczenie bo będzie odywać się ruch drugiego gracza
				changePlayer(); // zmiana gracza
			}

			// Gracz atakuje 
			if (board.isAttack(mouse.getX(), mouse.getY()))
			{
				//znalezienie wybranego pionka na tej pozycji - PRZESZUKANIE PIONKÓW I PORÓWNANIE WSPÓŁRZĘDNYCH 
				for (int i = 0; i < 32; i++)
				{
					if (object[i]->getX() == mouse.getX() && object[i]->getY() == mouse.getY())
					{

						object[i]->kill();
						object[id]->setPosition(mouse.getX(), mouse.getY());

						if (object[id]->getFigure() == PAWN)
							pawn[id].moved();

						board.reset(); // resetujemy tablicę aby zlikwidować niepotrzebne już podświetleenia na planszy
						mouse.resetFocus();

						changePlayer(); // zmiana gracza
						break;
						/*
						switch (object[i]->getFigure())
						{
						case PAWN:
						pawn[id].attack(object[i]);
						pawn[id].setPosition(mouse.getX(), mouse.getY());
						break;

						case BISHOP:
						//bishop[i - 16].
						break;

						case ROOK:
						//rook[i - 20].
						break;

						case KNIGHT:
						knight[id - 24].attack(object[i]);
						knight[id - 24].setPosition(mouse.getX(), mouse.getY());
						break;

						case QUEEN:
						//queen[i - 28].
						break;

						case KING:
						//king[i - 30].
						break;
						}
						*/
					}
				}
			}
		}
	}

	void render()
	{
		SDL_RenderClear(renderer);

		background.render();
		board.renderBoard(debug);

		for (int i = 0; i < 32; i++)
			object[i]->render(renderer);

		SDL_RenderPresent(renderer);
	}

public:
	void start()
	{
		/* KONFIGURACJA SDL */
		SDL_Init(SDL_INIT_EVERYTHING); //załączamy SDLa
		TTF_Init();
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

	void end();

	void close()
	{
		SDL_Quit();
	}
};
#endif _Game_H_