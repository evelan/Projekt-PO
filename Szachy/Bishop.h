#include "DynamicObject.h"

class Bishop : public DynamicObject
{
public:
	Bishop()
	{
		figure = BISHOP;
	}

	void move()
	{
		//setPosition(getX(), (getColor() == WHITE) ? getY() - 1 : getY() + 1);
	}

	void focus(SDL_Renderer *renderer, Board &board)
	{
		/* JEDNO W POLE PRZ�D USTAWI NA ZIELONE/CZERWONE */
		for (int i = 0; i < 7; i++)
			board.setPlaceAllow(getX() + i, getY() + i);
	}
};