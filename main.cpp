#include <SFML/Graphics.hpp>
#include <iostream>
#include "headers/Game.h"
#include "headers/Collision.h"
#include "headers/Consts.h"
#include "SFML/Audio.hpp"

int WIDTH = 1024;
int HEIGHT = 768;
int NUM_PERSONS = 5; // promeniti po dodavanju
int CURRENT_PERSON = 0;

int main(int argc, char *argv[])
{
	Game game;
  sf::Music music;
  if(!music.openFromFile("./assets/Sounds/start_game.wav"))
  {
    std::cout << "ERROR"<< std::endl;
  }
  else
  {
    music.setVolume(60);
		music.setLoop(true);

    music.play();
  }
	game.Run();

	return 0;
}
