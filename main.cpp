#ifdef __linux__
	#include <SFML/Graphics.hpp>
	#include <iostream>
	#include "headers/Game.h"
	#include "headers/Collision.h"
	#include "headers/Consts.h"
#elif defined _WIN32
	#include <SFML\Graphics.hpp>
	#include "headers\Game.h"
#endif

int WIDTH = 1920;
int HEIGHT = 1080;

int main(int argc, char *argv[])
{
	std::cout << argv[0] << std::endl;
	Game game;
	game.Run();

	return 0;
}
