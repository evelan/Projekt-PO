#ifndef _Board_H_
#define _Board_H_
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Place.h"

using namespace std;

class Board
{
private:
	bool white;
	int k;
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	int boardStartX = ((SCREEN_WIDTH - 8 * Place::TILE_SIZE) / 2); //gdzie zaczyna siê plansza do gry
	int boardStartY = ((SCREEN_HEIGHT - 8 * Place::TILE_SIZE) / 2);
	SDL_Renderer *renderer;

public:
	Place place[8][8];
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

	void renderBoard()
	{
		for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			place[j][i].render(renderer);
	}

	void setBusy(int x, int y, ENUM_STATE state)
	{
		place[x][y].setState(state);
	}

	void setFree(int x, int y)
	{
		place[x][y].setState(FREE);
	}

	void setPlaceAllow(int x, int y)
	{
		place[x][y].allow();
	}

	void resetAll()
	{
		for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			place[j][i].reset();
	}

	bool isFree(int x, int y)
	{
		return (place[x][y].getState() == FREE) ? true : false;
	}

	bool isEnemy(int x, int y)
	{
		return (place[x][y].getState() == FREE) ? true : false;
	}
};
#endif _Board_H_