#ifndef _Texture_H_
#define _Texture_H_
#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

/* NIESTANDARDOWE OBRAZKI NA EKRANIE */

class Texture
{
private:
	SDL_Rect rectangle; 
	SDL_Texture *texture;
	SDL_Renderer *renderer;

public:
	Texture(){}

	Texture(SDL_Renderer *renderer, string &file, int x, int y, int w, int h)
	{
		this->renderer = renderer;
		texture = IMG_LoadTexture(renderer, file.c_str());
		rectangle.x = x;
		rectangle.y = y;

		rectangle.w = w;
		rectangle.h = h;
	}

	void setup(SDL_Renderer *renderer, const string &file, int x, int y, int w, int h)
	{
		this->renderer = renderer;
		texture = IMG_LoadTexture(renderer, file.c_str());
		rectangle.x = x;
		rectangle.y = y;

		rectangle.w = w;
		rectangle.h = h;
	}

	void render()
	{
		SDL_RenderCopy(renderer, texture, NULL, &rectangle);
	}
};
#endif _Texture_H_