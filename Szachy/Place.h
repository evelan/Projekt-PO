#ifndef _Place_H_
#define _Place_H_
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

using namespace std;

enum ENUM_STATE
{
	WHITE_FIGURE = 0,
	BLACK_FIGURE = 1,
	FREE = 2
};
/* POJEDYÑCZE POLE NA SZACHOWNICY */

class Place
{
private:
	SDL_Texture *texture;
	SDL_Texture *green, *red;
	SDL_Rect rectangle;
	bool isAllow;
	ENUM_STATE state;

public:
	static const int TILE_SIZE = 64; //rozmiar jednej "kratki" planszy w pikselach
	Place()
	{
		rectangle.w = TILE_SIZE;
		rectangle.h = TILE_SIZE;
		isAllow = false;
		state = FREE;
	};

	void setup(SDL_Renderer *renderer, const string &file, int xPix, int yPix)
	{
		texture = IMG_LoadTexture(renderer, file.c_str());
		green = IMG_LoadTexture(renderer, "ok.png");
		red = IMG_LoadTexture(renderer, "not_ok.png");

		rectangle.x = xPix;
		rectangle.y = yPix;
	}

	void render(SDL_Renderer *renderer)
	{
		SDL_RenderCopy(renderer, texture, NULL, &rectangle);
		
		if (state == FREE && isAllow)
			SDL_RenderCopy(renderer, green, NULL, &rectangle);

		//if (state == BUSY)
		//	SDL_RenderCopy(renderer, red, NULL, &rectangle);
	}
	
	void allow()
	{
		isAllow = true;
	}

	void reset()
	{
		isAllow = false;
	}
	

	ENUM_STATE getState()
	{
		return state;
	}

	void setState(ENUM_STATE state)
	{
		this->state = state;
	}
};
#endif _Place_H_