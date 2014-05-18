#include "DynamicObject.h"

class Bishop : public DynamicObject
{
private:
	DIRECTION dir;

public:
	Bishop()
	{
		figure = BISHOP;
	}

	void focus()
	{
		if (isAlive())
		{
			// sprawdzanie do przodu w prawo
			int xDelta = getX() + 1;
			int yDelta = (getColor() == WHITE) ? (getY() - 1) : (getY() + 1);
			check(xDelta, yDelta, FOR_RIGHT);

			// ty³ prawo
			xDelta = getX() + 1;
			yDelta = (getColor() == WHITE) ? (getY() + 1) : (getY() - 1);
			check(xDelta, yDelta, BACK_RIGHT);

			// przód w lewo
			xDelta = getX() - 1;
			yDelta = (getColor() == WHITE) ? (getY() - 1) : (getY() + 1);
			check(xDelta, yDelta, FOR_LEFT);

			// ty³ w lewo 
			xDelta = getX() - 1;
			yDelta = (getColor() == WHITE) ? (getY() + 1) : (getY() - 1);
			check(xDelta, yDelta, BACK_LEFT);
		}
	}

private:
	void check(int xDelta, int yDelta, DIRECTION dir)
	{
		while (boardPtr->onBoard(xDelta, yDelta) && (boardPtr->isFree(xDelta, yDelta) || boardPtr->isEnemy(xDelta, yDelta, getColor())))
		{
			if (boardPtr->isFree(xDelta, yDelta))
				boardPtr->setAllow(xDelta, yDelta);
			else if (boardPtr->isEnemy(xDelta, yDelta, getColor())){
				boardPtr->setEnemy(xDelta, yDelta);
				break;
			}
			switch (dir)
			{
			case FOR_RIGHT:
				(getColor() == WHITE) ? yDelta-- : yDelta++;
				xDelta++;
				break;

			case BACK_RIGHT:
				(getColor() == WHITE) ? yDelta++ : yDelta--;
				xDelta++;
				break;

			case FOR_LEFT:
				(getColor() == WHITE) ? yDelta-- : yDelta++;
				xDelta--;
				break;

			case BACK_LEFT:
				(getColor() == WHITE) ? yDelta++ : yDelta--;
				xDelta--;
				break;
			}

		}
	}
};