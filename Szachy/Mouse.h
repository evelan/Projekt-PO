#include <SDL.h>

/* OBIEKT MYSZKI POZWALA NA ODBIERANIE SYGNA£ÓW */

class Mouse
{
private:

	int x;
	int y;
	SDL_Event e;

	bool focus;

	int boardStartX = ((800 - 8 * 64) / 2); //gdzie zaczyna siê plansza do gry
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

	bool overlaps(int figureX, int figureY)
	{
		return (x == figureX && y == figureY) ? true : false;
	}

	bool bPressed()
	{
		x = ((e.motion.x - boardStartX) / 64); // zapisanie wspó³rzêdnych podczas klikniecia bo tylko na takich nam zale¿y
		y = ((e.motion.y - boardStartY) / 64);
		return (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT);
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