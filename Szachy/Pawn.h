#include "DynamicObject.h"

class Pawn : public DynamicObject
{
private:
	bool firstMove; //czy ju� si� pionek ruszy�, je�li nie to mo�e wykona� 2 ruchy do przodu

public:
	Pawn()
	{
		figure = PAWN;
		firstMove = true;
	}

	void move(int x, int y)
	{
		firstMove = false;
		if (isAlive())
			setPosition(x, y);
	}

	void focus()
	{
		if (isAlive())
		{
			int xDelta = getX();
			int yDelta = (getColor() == WHITE) ? (getY() - 1) : (getY() + 1);
			if (boardPtr->isFree(xDelta, yDelta) && boardPtr->onBoard(xDelta, yDelta)) // je�li pole przed nim jest WOLNE i znajduje sie na szachownicy
			{
				boardPtr->setAllow(xDelta, yDelta); // to ustaw pole przed nim na ZIELONE
				if (boardPtr->isFree(getX(), (getColor() == WHITE) ? (getY() - 2) : (getY() + 2)) && firstMove) // je�li 2 pola przed nim jest WOLNE i pionek si� nie rusza�
					boardPtr->setAllow(getX(), (getColor() == WHITE) ? (getY() - 2) : (getY() + 2)); // to ustaw 2 pola przed nim na ZIELONE
			}

			xDelta = getX() - 1;
			if (boardPtr->isEnemy(xDelta, yDelta, getColor())) // je�li pole na lewo na skos jest WROGIEM
				boardPtr->setEnemy(xDelta, yDelta); // to ustaw to pole na CZERWONE

			xDelta = getX() + 1;
			if (boardPtr->isEnemy(xDelta, yDelta, getColor()))  // je�li pole na w prawo na skos jest WROGIEM 
				boardPtr->setEnemy(xDelta, yDelta); // to ustaw to pole na CZERWONE
		}
	}

	void attack(DynamicObject *obj)
	{
		firstMove = false;
		obj->kill();
	}
};