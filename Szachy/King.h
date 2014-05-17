#include "DynamicObject.h"

class King : public DynamicObject
{
public:
	King()
	{
		figure = KING;
	}

	void move(int x, int y)
	{
		if (isAlive())
			setPosition(x, y);
	}

	void focus()
	{
		if (isAlive())
		{
			if (boardPtr->isFree(getX(), getY() - 3)) // jeœli pole przed nim jest WOLNE
				boardPtr->setAllow(getX(), getY() - 3); // to ustaw pole przed nim na ZIELONE
		}
	}
};