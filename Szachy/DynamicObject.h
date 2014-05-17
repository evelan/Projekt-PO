#ifndef _DynamicObject_H_
#define _DynamicObject_H_
#include <SDL.h>
#include <SDL_image.h>
#include "Board.h"

enum FIGURE_TYPE
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
	COLOR colorFigure; //ustawiany tylko raz wiêc prywatny
	const int TILE_SIZE = 64; // wielkoœæ pionka w pixelach
	bool live;
	int x, y; // pozycja pionka w jednostakch na planszy

protected:
	FIGURE_TYPE figure; //mo¿e siê zmieniæ
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
		boardPtr->setFree(x, y);
	}

	void set(SDL_Renderer *renderer, int x, int y, COLOR colorFigure, Board &board)
	{
		this->renderer = renderer;
		boardPtr = &board;
		
		switch (figure) //która textura ma byæ za³adowana
		{
		case PAWN:
			texture = IMG_LoadTexture(renderer, ((colorFigure == WHITE) ? "WPawn.png" : "BPawn.png"));
			break;

		case ROOK:
			texture = IMG_LoadTexture(renderer, ((colorFigure == WHITE) ? "WRook.png" : "BRook.png"));
			break;
			
		case KING:
			texture = IMG_LoadTexture(renderer, ((colorFigure == WHITE) ? "WKing.png" : "BKing.png"));
			break;

		case QUEEN:
			texture = IMG_LoadTexture(renderer, ((colorFigure == WHITE) ? "WQueen.png" : "BQueen.png"));
			break;

		case BISHOP:
			texture = IMG_LoadTexture(renderer, ((colorFigure == WHITE) ? "WBishop.png" : "BBishop.png"));
			break;
			
		case KNIGHT:
			texture = IMG_LoadTexture(renderer, ((colorFigure == WHITE) ? "WKnight.png" : "BKnight.png"));
			break;
		}

		setPosition(x, y, true);
		board.setBusy(x, y, colorFigure);
		this->colorFigure = colorFigure;

		//rectangle.w = TILE_SIZE;
		//rectangle.h = TILE_SIZE;
	}

	void setPosition(int x, int y, bool firstSetup = false)
	{
		if (!firstSetup)
			boardPtr->setFree(getX(), getY());

		/* POZYCJA NA PLANSZY [0, 7] */
		this->x = x;
		this->y = y;

		/* POZYCJA W PIXELACH - NA EKRANIE */
		int boardStartX = ((800 - 8 * TILE_SIZE) / 2);
		int boardStartY = ((600 - 8 * TILE_SIZE) / 2);

		rectangle.x = (x * TILE_SIZE) + boardStartX;
		rectangle.y = (y * TILE_SIZE) + boardStartY;

		boardPtr->setBusy(x, y, getColor()); // tu pobiera dobrze wartosci z getX i getY potem siê psuje
	}

	void render(SDL_Renderer *renderer)
	{
		rectangle.w = TILE_SIZE;
		rectangle.h = TILE_SIZE;

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

	COLOR getColor()
	{
		return colorFigure;
	}

	FIGURE_TYPE getFigure()
	{
		return figure;
	}
};
#endif _DynamicObject_H_