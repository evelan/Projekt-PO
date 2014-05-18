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
		int xDelta = getX();
		int yDelta = getY() - 1;
			for (int i = 0; i < 8; i++){
				if (boardPtr->onBoard(xDelta, yDelta))
				{
					if (boardPtr->isFree(xDelta, yDelta)) {
						boardPtr->setAllow(xDelta, yDelta);
					}
					else if (boardPtr->isEnemy(xDelta, yDelta, getColor())){
						boardPtr->setEnemy(xDelta, yDelta);
					}
				}
				if (i == 0)	{ xDelta++; }
				if (i == 1) { yDelta++; }
				if (i == 2) { yDelta++; }
				if (i == 3) { xDelta--; }
				if (i == 4)	{ xDelta--; }
				if (i == 5) { yDelta--; }
				if (i == 6)	{ yDelta--; }
			}
		}
	}
};