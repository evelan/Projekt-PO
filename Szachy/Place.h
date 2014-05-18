#ifndef _Place_H_
#define _Place_H_
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Text.h"
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

/* KLASA REPREZENTUJE JEDNO POLE NA SZACHOWNICY */

class Place
{
private:
	SDL_Texture *green, *red;
	SDL_Texture *black, *white;
	SDL_Texture *texture;
	SDL_Rect rectangle;
	STATE state;
	COLOR color;
	Text napis;
	int x, y;

public:
	static const int TILE_SIZE = 64; //rozmiar jednej "kratki" planszy w pikselach
	bool allowedPlace; // pole dozwolone dla ruchu, publiczne �eby ograniczy� liczb� "getter�w" i "setter�w" w tej klasie
	bool attackAllow; // pole na kt�rym jest przeciwnik

	Place()
	{
		rectangle.w = TILE_SIZE;
		rectangle.h = TILE_SIZE;
		allowedPlace = false;
		attackAllow = false;
		state = FREE; // standardowo wszystkie pola s� wolne
		color = NONE; // i nie ma na nich pionk�w �adnego koloru
	};

	void setup(SDL_Renderer *renderer, const string &file, int xPix, int yPix)
	{
		texture = IMG_LoadTexture(renderer, file.c_str());
		green = IMG_LoadTexture(renderer, "ok.png");
		red = IMG_LoadTexture(renderer, "not_ok.png");
		black = IMG_LoadTexture(renderer, "black.png");
		white = IMG_LoadTexture(renderer, "white.png");

		rectangle.x = xPix;
		rectangle.y = yPix;

		napis.setup(renderer);
		napis.setPosition(xPix, yPix);
	}

	void render(SDL_Renderer *renderer, bool debug = false) // renderuje pole na wedle ustawie�
	{
		SDL_RenderCopy(renderer, texture, NULL, &rectangle); // czarne/bia�e jest renderowane zawsze
		
		if (state == BUSY && attackAllow) //czerwona nak�adka je�li jest na nim przeciwnik i jest zaj�te
			SDL_RenderCopy(renderer, red, NULL, &rectangle);

		if (state == FREE && allowedPlace) //zielona nak�adka je�li dost�pne dla ruchu i wolne
			SDL_RenderCopy(renderer, green, NULL, &rectangle);

		
		/*
		if (getColor() == BLACK)
			napis.setText("BL");
		else if (getColor() == WHITE)
			napis.setText("WH");
		else if (getColor() == NONE)
			napis.setText("NON");

		napis.render();
		*/
		if (debug) {
			if (state == FREE) //zielona nak�adka je�li dost�pne dla ruchu i wolne
				SDL_RenderCopy(renderer, green, NULL, &rectangle);

			if (state == BUSY) //czerwona nak�adka je�li jest na nim przeciwnik i jest zaj�te
				SDL_RenderCopy(renderer, red, NULL, &rectangle);

			if (getColor() == WHITE)
				SDL_RenderCopy(renderer, white, NULL, &rectangle);

			if (getColor() == BLACK)
				SDL_RenderCopy(renderer, black, NULL, &rectangle);
		}
	}

	void reset() // resetuje ustawienia pola
	{
		allowedPlace = false;
		attackAllow = false;
	}

	STATE getState() // zwraca informacj� WOLNE / ZAJ�TE
	{
		return state;	
	}

	COLOR getColor() // zwraca informacj� jakiego koloru pionek jest na tym polu
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