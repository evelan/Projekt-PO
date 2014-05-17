#include "DynamicObject.h"

class Bishop : public DynamicObject
{
public:
	Bishop()
	{
		figure = BISHOP;
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
			int xDelta = getX() - 10;
			//int i = 0;
			/*
			while (boardPtr->isFree(xDelta + i, yDelta + i))
			{
				if (boardPtr->onBoard(xDelta + i, yDelta + i))
					boardPtr->setAllow(xDelta + i, yDelta + i);
				i++;
			}
			*/
			/*
			do
			{
				i++;
				if (boardPtr->onBoard(xDelta + i, yDelta + i))
					boardPtr->setAllow(xDelta + i, yDelta + i);
			} while (!boardPtr->isEnemy(xDelta + i, yDelta + i, getColor()));
			*/
			
			for (int i = 0; i < 20; i++) {
				if (boardPtr->onBoard(xDelta+i, yDelta+i))
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

private:
	int nextPlace()
	{
		return 0;
	}
};