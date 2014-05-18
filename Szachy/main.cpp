#include "Game.h"

int main(int argc, char *argv[]) {
	Game game;
	game.start();
	game.mainLoop();
	game.close();

	return 0;
}