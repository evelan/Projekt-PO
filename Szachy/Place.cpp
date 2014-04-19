#include <SDL.h>
#include <SDL_image.h>
#include "Texture.cpp"

enum STATE_ENUM
{
	FREE = 0,
	FRIEND = 1,
	ENEMY = 2
};

enum COLOR_ENUM
{
	WHITE = 0,
	BLACK = 1
};

class Place : public Texture
{
protected:
	int TILE_SIZE = 64;
	STATE_ENUM state = FREE;
	COLOR_ENUM color = WHITE;

public:
	Place(){}

	SDL_Texture *loadTexture(SDL_Renderer *ren, int x, int y, bool white)
	{
		if (white) {
			texture = IMG_LoadTexture(ren, "white_place.png");
			color = WHITE;
		}
		else {
			texture = IMG_LoadTexture(ren, "black_place.png");
			color = BLACK;
		}

		rectangle.x = x;
		rectangle.y = y;
		rectangle.w = TILE_SIZE;
		rectangle.h = TILE_SIZE;
		return texture;
	}

};