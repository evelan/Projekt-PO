#include <SDL.h>
#include <SDL_image.h>
#include "Place.h"


class Board
{
private:
	Place boardMap[8][8];
	int offset_x = (800 - (64 * 8)) / 2;
	int offset_y = (600 - (64 * 8)) / 2;
	bool white;
	int k;

public:
	Board(SDL_Renderer *renderer)
	{
		white = false;
		k = 0;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				white = (k++ % 2) ? true : false; // na zmianê
				if (j == 7)	k++; // jak ostatni "kafelek to dodajemy +1 ¿eby kolejny by³ tego samego koloru co poprzedni
				boardMap[j][i].loadTexture(renderer, (offset_x + (64 * j)), (offset_y + (64 * i)), white);
			}
		}
	}

	void render(SDL_Renderer *renderer)
	{
		for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			boardMap[j][i].render(renderer);
	}

	~Board()
	{

	}

};