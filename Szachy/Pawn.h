#include "DynamicObject.h"

class Pawn : public DynamicObject
{
private:
	static int defX;
	static int defY;
	int x;
	int y;

public:
	Pawn() { setSize(TILE_SIZE); }

	void set(SDL_Renderer *ren, int pos_x, int pos_y, COLOR_ENUM value)
	{
		int boardStartX = ((800 - 8 * TILE_SIZE) / 2);
		int boardStartY = ((600 - 8 * TILE_SIZE) / 2);
		loadTexture(ren, ((value == WHITE) ? "WPawn.png" : "BPawn.png")); // je�li prawda (WHITE) to �aduje texture bia�ego pionka
		
		
		setPosition(boardStartX + TILE_SIZE * pos_x, boardStartY + TILE_SIZE * pos_y);
		
		
		color = value;
	}

	void move()
	{
		setPosition(getX(), (getColor() == WHITE) ? getY() - TILE_SIZE : getY() + TILE_SIZE);
	}

	void focus()
	{

	}

	void attack()
	{

	}
};