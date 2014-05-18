#include <SDL.h>
#include "DynamicObject.h"
#include "Game.h"

/* OBIEKT MYSZKI POZWALA NA ODBIERANIE SYGNA£ÓW */

class Mouse
{
private:
	int boardStartX = ((800 - 8 * 64) / 2); //gdzie zaczyna siê plansza do gry
	int boardStartY = ((600 - 8 * 64) / 2);
	SDL_Event e;
	bool focus;
	int x;
	int y;

public:
	Mouse()
	{
		focus = false;
	}

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
		return (obj->getX() == x && obj->getY() == y);
	}

	bool bPressed()
	{
		if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
		{
			x = ((e.motion.x - boardStartX) / 64); // zapisanie wspó³rzêdnych podczas klikniecia bo tylko na takich nam zale¿y
			y = ((e.motion.y - boardStartY) / 64);
			return true;
		}
		else
			return false;
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