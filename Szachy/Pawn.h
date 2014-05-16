#include "DynamicObject.h"

class Pawn : public DynamicObject
{
private:
	bool isMoved; //czy ju¿ siê pionek ruszy³, jeœli nie to mo¿e wykonaæ 2 ruchy do przodu

public:
	Pawn()
	{
		figure = PAWN;
		isMoved = false;
	}

	void move()
	{
		if (isAlive())
		{
			boardPtr->setFree(getX(), getY());
			setPosition(getX(), (getColor() == WHITE) ? (getY() - 1) : (getY() + 1));
			isMoved = true;
			boardPtr->setBusy(getX(), getY(), getColor());
		}
	}

	void focus()
	{
		if (isAlive())
		{
			boardPtr->reset(); // resetuje ca³¹ tablicê domyœlnych kolorów przed "focusowaniem"

			if (boardPtr->isFree(getX(), (getColor() == WHITE) ? (getY() - 1) : (getY() + 1))) // jeœli pole przed nim jest WOLNE
			{
				boardPtr->setAllow(getX(), (getColor() == WHITE) ? (getY() - 1) : (getY() + 1)); // to ustaw pole przed nim na ZIELONE
				//if (boardPtr->isFree(getX(), (getColor() == WHITE) ? (getY() - 2) : (getY() + 2) && !isMoved)) // jeœli 2 pola przed nim jest WOLNE i pionek siê nie rusza³
					//boardPtr->setAllow(getX(), (getColor() == WHITE) ? (getY() - 2) : (getY() + 2)); // to ustaw 2 pola przed nim na ZIELONE
			}

			if (boardPtr->isEnemy(getX() - 1, (getColor() == WHITE) ? (getY() - 1) : (getY() + 1), getColor())) // jeœli pole na lewo na skos jest WROGIEM
				boardPtr->setEnemy(getX() - 1, (getColor() == WHITE) ? (getY() - 1) : (getY() + 1)); // to ustaw to pole na CZERWONE

			if (boardPtr->isEnemy(getX() + 1, (getColor() == WHITE) ? (getY() - 1) : (getY() + 1), getColor()))  // jeœli pole na w prawo na skos jest WROGIEM 
				boardPtr->setEnemy(getX() + 1, (getColor() == WHITE) ? (getY() - 1) : (getY() + 1)); // to ustaw to pole na CZERWONE
		}
	}

	

	void attack()
	{
		if (isAlive())
			isMoved = true;
	}

private:
	int inFront(int front = 1)
	{
		return ((getColor() == WHITE) ? (getY() - front) : (getY() + front));
	}
};