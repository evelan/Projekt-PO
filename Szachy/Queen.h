#include "DynamicObject.h"

class Queen : public DynamicObject
{
public:
	Queen()
	{
		figure = QUEEN;
	}

	void focus()
	{
		if (isAlive())
		{

			// sprawdzanie do przodu
			int xDelta = getX();
			int yDelta = (getColor() == WHITE) ? (getY() - 1) : (getY() + 1);
			check(xDelta, yDelta, FORWARD);

			// ty³
			yDelta = (getColor() == WHITE) ? (getY() + 1) : (getY() - 1);
			check(xDelta, yDelta, BACKWARD);

			//w prawo 
			xDelta = getX() + 1;
			yDelta = getY();
			check(xDelta, yDelta, RIGHT);

			//w lewo 
			xDelta = getX() - 1;
			check(xDelta, yDelta, LEFT);

			// sprawdzanie do przodu w prawo
			xDelta = getX() + 1;
			yDelta = (getColor() == WHITE) ? (getY() - 1) : (getY() + 1);
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
			case FORWARD:
				(getColor() == WHITE) ? yDelta-- : yDelta++;
				break;

			case BACKWARD:
				(getColor() == WHITE) ? yDelta++ : yDelta--;
				break;

			case LEFT:
				xDelta--;
				break;

			case RIGHT:
				xDelta++;
				break;

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