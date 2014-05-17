#include <SDL.h>
#include "DynamicObject.h"
#include "Game.h"

/* OBIEKT MYSZKI POZWALA NA ODBIERANIE SYGNA��W */

class Mouse
{
private:

	int x;
	int y;
	SDL_Event e;

	bool focus;

	int boardStartX = ((800 - 8 * 64) / 2); //gdzie zaczyna si� plansza do gry
	int boardStartY = ((600 - 8 * 64) / 2);

public:
	Mouse()
	{
		focus = false;
	}

	~Mouse(){}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}

	bool overlaps(DynamicObject *obj)
	{
		return (obj->getX() == x && obj->getY() == y) ? true : false;
	}

	bool overlaps(DynamicObject *obj, int figureX, int figureY)
	{
		return (obj->getX() + figureX == x && obj->getY() + figureY == y) ? true : false;
	}

	bool bPressed()
	{
		x = ((e.motion.x - boardStartX) / 64); // zapisanie wsp�rz�dnych podczas klikniecia bo tylko na takich nam zale�y
		y = ((e.motion.y - boardStartY) / 64);
		return (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT);
	}

	bool kPressed(SDL_Keycode key)
	{
		return (e.type == key);
	}

	void setFocus()
	{
		focus = true;
	}

	void resetFocus()
	{
		focus = false;
	}

	bool isFocused()
	{
		return focus;
	}

	bool quit()
	{
		return (SDL_PollEvent(&e) != 0) || (e.type != SDL_QUIT);
	}
};