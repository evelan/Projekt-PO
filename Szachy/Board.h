#ifndef _Board_H_
#define _Board_H_
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Place.h"
using namespace std;

/* KLASA SPINA WSZYSTKIE POLA W OBIEKT SZACHOWNICY */

class Board
{
private:
	SDL_Renderer *renderer;
	Place place[8][8];
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	int boardStartX = ((SCREEN_WIDTH - 8 * Place::TILE_SIZE) / 2); //gdzie zaczyna siê plansza do gry
	int boardStartY = ((SCREEN_HEIGHT - 8 * Place::TILE_SIZE) / 2);
	bool white;
	int k;

public:
	Board(){};

	void setup(SDL_Renderer *renderer)
	{
		this->renderer = renderer;
		white = false;
		k = 0;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				white = (k++ % 2) ? true : false; // na zmianê true i false
				if (j == 7)	k++; // jak ostatni "kafelek to dodajemy +1 ¿eby kolejny by³ tego samego koloru co poprzedni
				place[j][i].setup(renderer, (white) ? "white_place.png" : "black_place.png", (boardStartX + (Place::TILE_SIZE * j)), (boardStartY + (Place::TILE_SIZE * i)));
			}
		}
	}

	void renderBoard(bool debug = false) // renderowanie szachownicy
	{
		for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			place[j][i].render(renderer, debug);
	}

	void reset() // zresetowanie ustawieñ pól szachownicy 
	{
		for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			place[j][i].reset();
	}

	/* USTAWIENIE ZAJÊTOŒCI POLA */
	void setBusy(int x, int y, COLOR color)
	{
		//if (onBoard(x, y)){
			place[x][y].setState(BUSY);
			place[x][y].setColor(color);
		//}
	}

	void setFree(int x, int y)
	{
		//if (onBoard(x, y)){
			place[x][y].setState(FREE);
			place[x][y].setColor(NONE);
		//}
	}

	bool isFree(int x, int y)
	{
		//if (onBoard(x, y))
			return (place[x][y].getState() == FREE);
	}

	bool isBusy(int x, int y)
	{
		//if (onBoard(x, y))
			return (place[x][y].getState() == BUSY);
	}

	/* USTAWIENIE CZY POLE JEST DOSTÊPNE DLA RUCHU */
	void setAllow(int x, int y)
	{
		//if (onBoard(x, y))
			place[x][y].allowedPlace = true;
	}

	bool isAllow(int x, int y)
	{
		//if (onBoard(x, y))
			return place[x][y].allowedPlace;
	}

	/* USTAWIENIE CZY NA POLU JEST PRZECIWNIK */
	void setEnemy(int x, int y)
	{
		//if (onBoard(x, y))
			place[x][y].attackAllow = true;
	}

	bool isAttack(int x, int y)
	{
		//if (onBoard(x, y))
			return place[x][y].attackAllow;
	}

	bool isEnemy(int x, int y, COLOR color) //czy dla wybranego obiektu inny pionek bêdzie przeciwnikiem
	{
		//if (onBoard(x, y)){
			if (place[x][y].getColor() == color)
				return false;
			else if (place[x][y].getColor() == NONE)
				return false;
			else
				return true;
		//}
	}

	bool onBoard(int x, int y)
	{
		return (x >= 0 && x <= 7 && y >= 0 && y <= 7);
	}

};
#endif _Board_H_