#pragma once

#ifdef __linux__
	#include <SFML/Graphics.hpp>
	#include <fstream>
	#include "Animation.h"
	#include "Consts.h"
#elif defined _WIN32
	#include <SFML\Graphics.hpp>
#endif
/*
*	Bazna klasa za sve objekte u igri
*/
class Organism
{
public:
  Organism();
  Organism(const sf::Texture&);

	void Resize();
  void Update();
	void Render(sf::RenderWindow &window);

	Animation *m_anim;
	sf::Sprite m_image;	//privatovati
protected:
	sf::Vector2f m_position;
	// Ako je u pitanju animacija, a ne staticna slika, dodati ovde objekat klase animacije
private:
	std::string m_name;
  int m_situation;
  int m_VEL_MIN = 1;
  int m_VEL_MAX = 2;
  int m_velocity;
};
