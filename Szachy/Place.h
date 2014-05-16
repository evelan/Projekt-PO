#ifndef _Place_H_
#define _Place_H_
#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

enum STATE
{
	FREE = 0,
	BUSY = 1
};

enum COLOR
{
	WHITE = 0,
	BLACK = 1,
	NONE = 2
};


/* POJEDY�CZE POLE NA SZACHOWNICY */

class Place
{
private:
	SDL_Texture *green, *red;
	SDL_Texture *texture;
	SDL_Rect rectangle;
	STATE state;
	COLOR color;


public:
	static const int TILE_SIZE = 64; //rozmiar jednej "kratki" planszy w pikselach
	bool allowedPlace; // pole dozwolone dla ruchu
	bool enemyHere; // pole na kt�rym jest przeciwnik

	Place()
	{
		rectangle.w = TILE_SIZE;
		rectangle.h = TILE_SIZE;
		allowedPlace = false;
		state = FREE; //standardowo wszystkie pola s� wolne
		color = NONE; 
	};

	void setup(SDL_Renderer *renderer, const string &file, int xPix, int yPix)
	{
		texture = IMG_LoadTexture(renderer, file.c_str());
		green = IMG_LoadTexture(renderer, "ok.png");
		red = IMG_LoadTexture(renderer, "not_ok.png");

		rectangle.x = xPix;
		rectangle.y = yPix;
	}

	void render(SDL_Renderer *renderer) // renderuje pole na wedle ustawie�
	{
		SDL_RenderCopy(renderer, texture, NULL, &rectangle); // czarne/bia�e jest renderowane zawsze
		
		if (state == FREE && allowedPlace) //zielona nak�adka je�li dost�pne dla ruchu i wolne
			SDL_RenderCopy(renderer, green, NULL, &rectangle);

		if (state == BUSY && enemyHere) //czerwona nak�adka je�li jest na nim przeciwnik i jest zaj�te
			SDL_RenderCopy(renderer, red, NULL, &rectangle);
	}

	void reset() // resetuje ustawienie pola
	{
		allowedPlace = false;
		enemyHere = false;
	}

	STATE getState()
	{
		return state;
	}

	COLOR getColor()
	{
		return color;
	}

	void setState(STATE state)
	{
		this->state = state;
	}

	void setColor(COLOR color)
	{
		this->color = color;
	}
};
#endif _Place_H_