#ifndef _DynamicObject_H_
#define _DynamicObject_H_
#include <SDL.h>
#include <SDL_image.h>
#include "Board.h"


enum DIRECTION
{
	FORWARD = 0,
	BACKWARD = 1,
	RIGHT = 2,
	LEFT = 3,

	FOR_RIGHT = 4,
	FOR_LEFT = 5,

	BACK_RIGHT = 6,
	BACK_LEFT = 7

};

enum FIGURE_TYPE
{
	PAWN = 0,
	BISHOP = 16,
	ROOK = 20,
	KNIGHT = 24,
	QUEEN = 28,
	KING = 30
};

/* KLASA BAZOWA PIONK�W */

class DynamicObject
{
private:
	const int TILE_SIZE = 64; // wielko�� pionka w pixelach
	int boardStartX = ((800 - 8 * TILE_SIZE) / 2);
	int boardStartY = ((600 - 8 * TILE_SIZE) / 2);
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Rect rectangle;
	COLOR colorFigure; //ustawiany tylko raz wi�c prywatny
	bool live;
	int x, y; // pozycja pionka w jednostakch na planszy

protected:
	FIGURE_TYPE figure; //mo�e si� zmieni�
	Board *boardPtr; //wska�nik na plansz�

public:
	DynamicObject(){}

	void set(SDL_Renderer *renderer, int x, int y, COLOR colorFigure, Board &board)
	{
		this->renderer = renderer;
		boardPtr = &board;
		live = true; // ka�dy tworzony pionek "�yje"
		switch (figure) //kt�ra textura ma by� za�adowana
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
		setPosition(obj->getX(), obj->getY()); // zmienia pozycj� na pozycj� pionka kt�rego atakuje
		obj->kill(); // pionek kt�ry zostaje zaatakowany ginie
	}

	void setPosition(int x, int y)
	{
		//ustawia obecn� pozcyj� jako woln� 
		boardPtr->setFree(getX(), getY());

		// zmienia wsp�rz�dne pionka
		this->x = x;
		this->y = y;

		//zmienia miejsce renderowania pionka
		rectangle.x = (x * TILE_SIZE) + boardStartX;
		rectangle.y = (y * TILE_SIZE) + boardStartY;

		//ustawia obecne miejsce jako zaj�te
		boardPtr->setBusy(x, y, colorFigure);
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