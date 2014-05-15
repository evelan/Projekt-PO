#ifndef _DynamicObject_H_
#define _DynamicObject_H_
#include <SDL.h>
#include <SDL_image.h>
#include "Board.h"

enum COLOR_ENUM
{
	WHITE = 0,
	BLACK = 1
};

enum FIGURE_ENUM
{
	PAWN = 0,
	KNIGHT = 1,
	BISHOP = 2,
	ROOK = 3,
	QUEEN = 4,
	KING = 5
};

/* KLASA BAZOWA PIONKÓW */

class DynamicObject 
{
private:
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Rect rectangle;
	COLOR_ENUM color; //ustawiany tylko raz wiêc prywatny
	const int TILE_SIZE = 64; // wielkoœæ pionka w pixelach
	bool live;
	int x, y; // pozycja pionka w jednostakch na planszy

protected:
	FIGURE_ENUM figure; //mo¿e siê zmieniæ
	Board *boardPtr; //wskaŸnik na planszê

public:
	DynamicObject()
	{
		live = true;
	};

	bool isAlive()
	{
		return live;
	}

	void kill()
	{
		live = false;
		boardPtr->resetAll();
	}

	void set(SDL_Renderer *renderer, int x, int y, COLOR_ENUM color, Board &board)
	{
		this->renderer = renderer;
		
		switch (figure) //która textura ma byæ za³adowana
		{
		case PAWN:
			texture = IMG_LoadTexture(renderer, ((color == WHITE) ? "WPawn.png" : "BPawn.png"));
			break;

		case ROOK:
			texture = IMG_LoadTexture(renderer, ((color == WHITE) ? "WRook.png" : "BRook.png"));
			break;
			
		case KING:
			texture = IMG_LoadTexture(renderer, ((color == WHITE) ? "WKing.png" : "BKing.png"));
			break;

		case QUEEN:
			texture = IMG_LoadTexture(renderer, ((color == WHITE) ? "WQueen.png" : "BQueen.png"));
			break;

		case BISHOP:
			texture = IMG_LoadTexture(renderer, ((color == WHITE) ? "WBishop.png" : "BBishop.png"));
			break;
			
		case KNIGHT:
			texture = IMG_LoadTexture(renderer, ((color == WHITE) ? "WKnight.png" : "BKnight.png"));
			break;

		}


		setPosition(x, y);
		board.setBusy(x, y, (getColor() == WHITE) ? WHITE_FIGURE : BLACK_FIGURE);
		
		this->color = color;
		boardPtr = &board;

		rectangle.w = TILE_SIZE;
		rectangle.h = TILE_SIZE;
	}

	void setPosition(int x, int y)
	{
		/* POZYCJA NA PLANSZY [0, 7] */
		this->x = x;
		this->y = y;

		/* POZYCJA W PIXELACH - NA EKRANIE */
		int boardStartX = ((800 - 8 * TILE_SIZE) / 2);
		int boardStartY = ((600 - 8 * TILE_SIZE) / 2);

		rectangle.x = (x * TILE_SIZE) + boardStartX;
		rectangle.y = (y * TILE_SIZE) + boardStartY;

		/* INFORMACJA O TYM ¯E POLE JEST ZAJÊTE */
	}

	void render()
	{
		if (live)
			SDL_RenderCopy(renderer, texture, NULL, &rectangle);
	}

	int getX() // pozycja na planszy
	{
		return x;
	}

	int getY() // pozycja na planszy
	{
		return y;
	}

	COLOR_ENUM getColor()
	{
		return color;
	}

	protected:
		bool safeMove()
		{
			return (x - 1 < 0 && x + 1 > 7 && y - 1 < 0 && y + 1 > 7) ? true : false;
		}

};
#endif _DynamicObject_H_