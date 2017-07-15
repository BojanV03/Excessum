#include <SFML/Graphics.hpp>
#include <iostream>
#include "headers/Game.h"
#include "headers/Collision.h"
#include "headers/Consts.h"

int WIDTH = 1024;
int HEIGHT = 768;
int NUM_PERSONS = 2; // promeniti po dodavanju

int main(int argc, char *argv[])
{
	Game game;
	game.Run();

	return 0;
}
