#include "game.h"
 
int main(int argc, char *argv[])
{
	auto game_instance = game();
	game_instance.start();

	return 0;
}