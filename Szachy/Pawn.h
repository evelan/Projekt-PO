
#include "DynamicObject.h"

class Pawn : public DynamicObject
{
private:
	bool isMoved;

public:
	Pawn()
	{
		figure = PAWN;
		isMoved = false;
	}

	void move()
	{
		if (!safeMove() && isAlive()) // sprawdza czy nie wyjdê za planszê robi¹c kolejny ruch
		{
			boardPtr->setFree(getX(), getY());
			setPosition(getX(), (getColor() == WHITE) ? getY() - 1 : getY() + 1);
			isMoved = true;
			boardPtr->setBusy(getX(), getY(), (getColor() == WHITE) ? WHITE_FIGURE : BLACK_FIGURE);
		}
	}

	void focus()
	{
		if (isAlive()){
			boardPtr->resetAll();

			/* JEDNO W POLE PRZÓD USTAWI NA ZIELONE/CZERWONE */
			if (boardPtr->isFree(getX(), (getColor() == WHITE) ? getY() - 1 : getY() + 1))
				boardPtr->setPlaceAllow(getX(), (getColor() == WHITE) ? getY() - 1 : getY() + 1);
			if (boardPtr->isEnemy(getX() + 1, (getColor() == WHITE) ? getY() - 1 : getY() + 1))
				boardPtr->setPlaceAllow(getX(), (getColor() == WHITE) ? getY() - 1 : getY() + 1);
		}
	}

	void attack()
	{
		if (isAlive())
			isMoved = true;
	}
};