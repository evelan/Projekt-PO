#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

class Texture
{
protected:
	SDL_Texture *texture;
	SDL_Rect rectangle;

public:
	Texture(SDL_Renderer *ren, const string &file, int x, int y, int w, int h)
	{
		texture = IMG_LoadTexture(ren, file.c_str());
		rectangle.x = x;
		rectangle.y = y;
		rectangle.w = w;
		rectangle.h = h;
		SDL_RenderCopy(ren, texture, NULL, &rectangle);
	}

	Texture(){}

	SDL_Texture *loadTexture(SDL_Renderer *ren, const string &file)
	{
		texture = IMG_LoadTexture(ren, file.c_str());
		return texture;
	}

	void setPosition(int x, int y)
	{
		rectangle.x = x;
		rectangle.y = y;
	}

	int getX()
	{
		return rectangle.x;
	}

	int getY()
	{
		return rectangle.y;
	}

	void render(SDL_Renderer *ren, int x, int y){
		rectangle.x = x;
		rectangle.y = y;
		SDL_RenderCopy(ren, texture, NULL, &rectangle);
	}

	void render(SDL_Renderer *ren){
		SDL_RenderCopy(ren, texture, NULL, &rectangle);
	}
};