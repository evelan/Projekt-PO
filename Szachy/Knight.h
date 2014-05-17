#include "DynamicObject.h"

class Knight : public DynamicObject
{
public:
	Knight()
	{
		figure = KNIGHT;
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
			int yDelta = getY() - 2;
			int xDelta = getX() - 1;
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
				if (i == 0)	{ xDelta += 2; }
				if (i == 1) { xDelta++; yDelta++; }
				if (i == 2) { yDelta += 2; }
				if (i == 3) { xDelta--; yDelta++; }
				if (i == 4)	{ xDelta -= 2; }
				if (i == 5) { xDelta--; yDelta--; }
				if (i == 6)	{ yDelta -= 2; }
			}
		}
	}

	void attack(DynamicObject *obj)
	{
		if (isAlive())
			obj->kill();
	}
};