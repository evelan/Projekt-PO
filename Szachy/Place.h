#ifndef _Place_H_
#define _Place_H_
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"

enum STATE_ENUM
{
	FREE = 0,
	BUSY = 1
};

class Place : public Texture
{
protected:
	const int TILE_SIZE = 64;
	STATE_ENUM state = FREE;

public:
	Place(){ setSize(TILE_SIZE); };

	STATE_ENUM getState()
	{
		return state;
	}

	void setState(STATE_ENUM state)
	{
		this->state = state;
	}

};
#endif _Place_H_