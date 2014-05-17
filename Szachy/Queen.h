#include "DynamicObject.h"

class Queen : public DynamicObject
{
public:
	Queen()
	{
		figure = QUEEN;
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
			int yDelta = getY() - 10;
			int xDelta = getX();

			for (int i = 0; i < 20; i++) {
				if (boardPtr->onBoard(xDelta, yDelta + i))
				{
					if (boardPtr->isFree(xDelta, yDelta + i))
						boardPtr->setAllow(xDelta, yDelta + i);
				}
			}
			yDelta = getY();
			xDelta = getX() - 10;
			for (int i = 0; i < 20; i++) {
				if (boardPtr->onBoard(xDelta + i, yDelta))
				{
					if (boardPtr->isFree(xDelta + i, yDelta))
						boardPtr->setAllow(xDelta + i, yDelta);
				}
			}

			yDelta = getY() - 10;
			xDelta = getX() - 10;
			for (int i = 0; i < 20; i++) {
				if (boardPtr->onBoard(xDelta + i, yDelta + i))
				{
					if (boardPtr->isFree(xDelta + i, yDelta + i))
						boardPtr->setAllow(xDelta + i, yDelta + i);
				}
			}

			yDelta = getY() - 10;
			xDelta = getX() + 10;
			for (int i = 0; i < 20; i++) {
				if (boardPtr->onBoard(xDelta - i, yDelta + i))
				{
					if (boardPtr->isFree(xDelta - i, yDelta + i))
						boardPtr->setAllow(xDelta - i, yDelta + i);
				}
			}
		}
	}
};