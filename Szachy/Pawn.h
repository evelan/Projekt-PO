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
			if (boardPtr->isFree(getX(), (getColor() == WHITE) ? (getY() - 1) : (getY() + 1))) // je�li pole przed nim jest WOLNE
			{
				boardPtr->setAllow(getX(), (getColor() == WHITE) ? (getY() - 1) : (getY() + 1)); // to ustaw pole przed nim na ZIELONE
				if (boardPtr->isFree(getX(), (getColor() == WHITE) ? (getY() - 2) : (getY() + 2)) && firstMove) // je�li 2 pola przed nim jest WOLNE i pionek si� nie rusza�
					boardPtr->setAllow(getX(), (getColor() == WHITE) ? (getY() - 2) : (getY() + 2)); // to ustaw 2 pola przed nim na ZIELONE
			}

			if (boardPtr->isEnemy(getX() - 1, (getColor() == WHITE) ? (getY() - 1) : (getY() + 1), getColor())) // je�li pole na lewo na skos jest WROGIEM
				boardPtr->setEnemy(getX() - 1, (getColor() == WHITE) ? (getY() - 1) : (getY() + 1)); // to ustaw to pole na CZERWONE

			if (boardPtr->isEnemy(getX() + 1, (getColor() == WHITE) ? (getY() - 1) : (getY() + 1), getColor()))  // je�li pole na w prawo na skos jest WROGIEM 
				boardPtr->setEnemy(getX() + 1, (getColor() == WHITE) ? (getY() - 1) : (getY() + 1)); // to ustaw to pole na CZERWONE
		}
	}

	

	void attack(DynamicObject *obj)
	{
		if (isAlive())
			firstMove = false;

		obj->kill();
	}

private:
	int inFront(int front = 1)
	{
		return ((getColor() == WHITE) ? (getY() - front) : (getY() + front));
	}
};