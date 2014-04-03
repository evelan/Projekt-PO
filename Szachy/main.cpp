#include <iostream>
#include <SDL.h>

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT = 0,
	KEY_PRESS_SURFACE_UP = 1,
	KEY_PRESS_SURFACE_DOWN = 2,
	KEY_PRESS_SURFACE_LEFT = 3,
	KEY_PRESS_SURFACE_RIGHT = 4,
	KEY_PRESS_SURFACE_TOTAL = 5
};

int main(int argc, char **argv){

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	bool quit = false;
	SDL_Event e;
	SDL_Surface * KeySurfaces[KEY_PRESS_SURFACE_TOTAL];
	SDL_Surface * CurrentSurface;
	SDL_Surface * ScreenSurface;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *Window = SDL_CreateWindow("Szachy!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); //tworzy okno
	ScreenSurface = SDL_GetWindowSurface(Window);

	KeySurfaces[KEY_PRESS_SURFACE_UP] = SDL_LoadBMP("C:/Users/Jakub/Documents/Visual Studio 2013/Projects/Szachy/img/up.bmp");
	KeySurfaces[KEY_PRESS_SURFACE_DOWN] = SDL_LoadBMP("C:/Users/Jakub/Documents/Visual Studio 2013/Projects/Szachy/img/down.bmp");
	KeySurfaces[KEY_PRESS_SURFACE_RIGHT] = SDL_LoadBMP("C:/Users/Jakub/Documents/Visual Studio 2013/Projects/Szachy/img/right.bmp");
	KeySurfaces[KEY_PRESS_SURFACE_LEFT] = SDL_LoadBMP("C:/Users/Jakub/Documents/Visual Studio 2013/Projects/Szachy/img/left.bmp");
	KeySurfaces[KEY_PRESS_SURFACE_DEFAULT] = SDL_LoadBMP("C:/Users/Jakub/Documents/Visual Studio 2013/Projects/Szachy/img/def.bmp");
	CurrentSurface = KeySurfaces[KEY_PRESS_SURFACE_DEFAULT];

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				//Select surfaces based on key press
				switch (e.key.keysym.sym)
				{
				case SDLK_DOWN:
					CurrentSurface = KeySurfaces[KEY_PRESS_SURFACE_DOWN];
					break;

				case SDLK_UP:
					CurrentSurface = KeySurfaces[KEY_PRESS_SURFACE_UP];
					break;

				case SDLK_RIGHT:
					CurrentSurface = KeySurfaces[KEY_PRESS_SURFACE_RIGHT];
					break;

				case SDLK_LEFT:
					CurrentSurface = KeySurfaces[KEY_PRESS_SURFACE_LEFT];
					break;

				default:
					CurrentSurface = KeySurfaces[KEY_PRESS_SURFACE_DEFAULT];
					break;

				}
			}
			//Apply the current image
			SDL_BlitSurface(CurrentSurface, NULL, ScreenSurface, NULL);

			//Update the surface
			SDL_UpdateWindowSurface(Window);
		}
	}
	SDL_Quit();

	return 0;
}