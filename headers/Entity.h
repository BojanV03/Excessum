#pragma once

#ifdef __linux__
	#include <SFML/Graphics.hpp>
#elif defined _WIN32
	#include <SFML\Graphics.hpp>
#endif
/*
*	Bazna klasa za sve objekte u igri
*/
class Entity
{
public:

	virtual ~Entity();

	virtual void Update(float dt) = 0;
	virtual void Render(sf::RenderWindow window) = 0;

protected:

	Entity(); // zabrana kreiranja Entity objekata
	Entity(sf::Vector2f position, sf::Texture);

	sf::Vector2f m_position;
	sf::Sprite m_image;
	// Ako je u pitanju animacija, a ne staticna slika, dodati ovde objekat klase animacije

};
