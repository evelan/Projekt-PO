#ifndef _Board_H_
#define _Board_H_
#include <SDL.h>
#include <SDL_image.h>
#include "Place.h"


class Board : public Place

{
private:
	bool white;
	int k;

protected:
	Place boardMap[8][8];
	int boardStartX = ((800 - 8 * TILE_SIZE) / 2); //gdzie zaczyna siê plansza do gry
	int boardStartY = ((600 - 8 * TILE_SIZE) / 2);

public:
	Board(){};

	Board(SDL_Renderer *renderer)
	{
		white = false;
		k = 0;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				white = (k++ % 2) ? true : false; // na zmianê true i false
				if (j == 7)	k++; // jak ostatni "kafelek to dodajemy +1 ¿eby kolejny by³ tego samego koloru co poprzedni
				
				boardMap[j][i].loadTexture(renderer, (white) ? "white_place.png" : "black_place.png");
				boardMap[j][i].setPosition((boardStartX + (TILE_SIZE * j)), (boardStartY + (TILE_SIZE * i)));
			}
		}
	}

	void renderBoard(SDL_Renderer *renderer)
	{
		for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			boardMap[j][i].render(renderer);
	}
};
#endif _Board_H_