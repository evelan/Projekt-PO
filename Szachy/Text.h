#ifndef _Text_H_
#define _Text_H_
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

class Text
{
private:
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Rect rectangle;
	SDL_Surface *surf;
	SDL_Color color;
	TTF_Font *font;
	string message;
	int fontSize;

public:
	Text()
	{
		color = { 255, 255, 255 };
		fontSize = 48;
		rectangle.x = 0;
		rectangle.y = 0;
		rectangle.h = 64;
		rectangle.w = 64;
	}

	void setText(string message)
	{
		this->message = message.c_str();
	}

	string getText()
	{
		return message;
	}

	void setFontSize(int fontSize)
	{
		this->fontSize = fontSize;
	}

	void setPosition(int x, int y)
	{
		rectangle.x = x;
		rectangle.y = y;
	}

	void setup(SDL_Renderer *renderer)
	{
		this->renderer = renderer;
	}

	void render()
	{
		font = TTF_OpenFont("arial.ttf", fontSize);

		if (surf == NULL)
			surf = TTF_RenderText_Blended(font, message.c_str(), color);
		if (texture == NULL)
			texture = SDL_CreateTextureFromSurface(renderer, surf);
		
		SDL_FreeSurface(surf);
		TTF_CloseFont(font);
		SDL_RenderCopy(renderer, texture, NULL, &rectangle);
	}
};
#endif _Text_H_