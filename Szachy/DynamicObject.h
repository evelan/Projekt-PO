#ifndef _DynamicObject_H_
#define _DynamicObject_H_
#include <SDL.h>
#include <SDL_image.h>
#include "Board.h"

enum FIGURE_TYPE
{
	PAWN = 0,
	BISHOP = 16,
	ROOK = 20,
	KNIGHT = 24,
	QUEEN = 28,
	KING = 30
};

/* KLASA BAZOWA PIONKÓW */

class DynamicObject
{
private:
	const int TILE_SIZE = 64; // wielkoœæ pionka w pixelach
	int boardStartX = ((800 - 8 * TILE_SIZE) / 2);
	int boardStartY = ((600 - 8 * TILE_SIZE) / 2);
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Rect rectangle;
	COLOR colorFigure; //ustawiany tylko raz wiêc prywatny
	bool live;
	int x, y; // pozycja pionka w jednostakch na planszy

protected:
	FIGURE_TYPE figure; //mo¿e siê zmieniæ
	Board *boardPtr; //wskaŸnik na planszê

public:
	DynamicObject()
	{
		live = true; // ka¿dy tworzony pionek "¿yje"
		rectangle.w = TILE_SIZE;
		rectangle.h = TILE_SIZE;
	};

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

		this->x = x;
		this->y = y;

		rectangle.x = (x * TILE_SIZE) + boardStartX;
		rectangle.y = (y * TILE_SIZE) + boardStartY;

		this->colorFigure = colorFigure;

		boardPtr->setBusy(getX(), getY(), getColor());
	}

	bool isAlive()
	{
		return live;
	}

	void kill()
	{
		live = false;
		boardPtr->setFree(x, y); // pole zostaje zwolnione 
	}

	void attack(DynamicObject *obj)
	{
		setPosition(obj->getX(), obj->getY()); // zmienia pozycjê na pozycjê pionka którego atakuje
		obj->kill(); // pionek który zostaje zaatakowany ginie
	}

	void setPosition(int x, int y)
	{
		//ustawia obecn¹ pozcyjê jako woln¹ 
		boardPtr->setFree(getX(), getY());

		// zmienia wspó³rzêdne pionka
		this->x = x;
		this->y = y;

		//zmienia miejsce renderowania pionka
		rectangle.x = (x * TILE_SIZE) + boardStartX;
		rectangle.y = (y * TILE_SIZE) + boardStartY;

		//ustawia obecne miejsce jako zajête
		boardPtr->setBusy(x, y, colorFigure);
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