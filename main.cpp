#include "Chess_game.h"

int main(){
	Game* game = new Chess_minigame;
	game->start();

	game->finish();
	return 0;
}