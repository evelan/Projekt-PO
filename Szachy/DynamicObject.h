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
	const int TILE_SIZE = 64;
	int unsigned id;

public:
	
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
};
#endif _DynamicObject_H_