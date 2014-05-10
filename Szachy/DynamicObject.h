#ifndef _DynamicObject_H_
#define _DynamicObject_H_
#include <SDL.h>
#include <iostream>
#include "Texture.h"

using namespace std;

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

class DynamicObject : public Texture
{
protected:
	bool live;
	COLOR_ENUM color;
	FIGURE_ENUM figure;
	int unsigned id;
	const int TILE_SIZE = 64;

public:

	DynamicObject(){};

	bool isAlive()
	{
		return live;
	}

	FIGURE_ENUM getFigureType()
	{
		return figure;
	}

	COLOR_ENUM getColor()
	{
		return color;
	}
	/*
	void set(SDL_Renderer *ren, int pos_x, int pos_y, COLOR_ENUM color, FIGURE_ENUM figure)
	{
		int boardStartX = ((800 - 8 * TILE_SIZE) / 2);
		int boardStartY = ((600 - 8 * TILE_SIZE) / 2);
		loadTexture(ren, ((color == WHITE) ? "WPawn.png" : "BPawn.png")); // jeœli prawda (WHITE) to ³aduje bia³ego pionka
		setPosition(boardStartX + TILE_SIZE * pos_x, boardStartY + TILE_SIZE * pos_y);
		this->color = color;
		this->figure = figure;
	}
	*/
};
#endif _DynamicObject_H_