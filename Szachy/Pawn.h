#include "DynamicObject.h"

class Pawn : public DynamicObject
{
private:
	bool firstMove; //czy ju¿ siê pionek ruszy³, jeœli nie to mo¿e wykonaæ 2 ruchy do przodu

public:
	Pawn()
	{
		figure = PAWN;
		firstMove = true;
	}

	void moved()
	{
		firstMove = false;
	}

	void focus()
	{
		if (isAlive())
		{
			int xDelta = getX();
			int yDelta = (getColor() == WHITE) ? (getY() - 1) : (getY() + 1);
			if (boardPtr->isFree(xDelta, yDelta) && boardPtr->onBoard(xDelta, yDelta)) // jeœli pole przed nim jest WOLNE i znajduje sie na szachownicy
			{
				boardPtr->setAllow(xDelta, yDelta); // to ustaw pole przed nim na ZIELONE
				if (boardPtr->isFree(getX(), (getColor() == WHITE) ? (getY() - 2) : (getY() + 2)) && firstMove) // jeœli 2 pola przed nim jest WOLNE i pionek siê nie rusza³
					boardPtr->setAllow(getX(), (getColor() == WHITE) ? (getY() - 2) : (getY() + 2)); // to ustaw 2 pola przed nim na ZIELONE
			}

			xDelta = getX() - 1;
			if (boardPtr->isEnemy(xDelta, yDelta, getColor()) && boardPtr->onBoard(xDelta, yDelta)) // jeœli pole na lewo na skos jest WROGIEM
				boardPtr->setEnemy(xDelta, yDelta); // to ustaw to pole na CZERWONE

			xDelta = getX() + 1;
			if (boardPtr->isEnemy(xDelta, yDelta, getColor()) && boardPtr->onBoard(xDelta, yDelta))  // jeœli pole na w prawo na skos jest WROGIEM 
				boardPtr->setEnemy(xDelta, yDelta); // to ustaw to pole na CZERWONE
		}
	}
};