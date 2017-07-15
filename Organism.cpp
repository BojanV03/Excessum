#include "headers/Organism.h"
#include <iostream>
Organism::Organism()
{

}

Organism::Organism(const sf::Texture &a)
{
	m_image.setTexture(a);
	m_situation = rand() % 2;
	int y = (rand() % (int)(HEIGHT/3)) + HEIGHT/3;

	std::ifstream input("assets/data/names.txt");
	int name = rand() % 200;
	std::string firstName, lastName;

	for(int i = 0; i < name; i++)
	{
		input >> firstName >> lastName;
	}

	m_name = std::string(firstName + " " + lastName);

	std::cout << m_name << std::endl;
	if(m_situation == 0)
	{
		m_image.setPosition(-m_image.getLocalBounds().width, y);
	}
	else
	{
		m_image.setPosition(WIDTH, y);
	}
	m_velocity = (rand() % (m_VEL_MAX-m_VEL_MIN))+m_VEL_MIN;
	float razmera;
	razmera = 0.22 + ((1.0*y-HEIGHT/3)/HEIGHT)*(0.66);
	m_image.setScale(razmera, razmera);
}

void Organism::Move ()
{		// Changing position of organism according to velocity in coordinate system
	if (m_situation == 0)
	{
		m_image.setPosition(m_image.getPosition().x + m_velocity, m_image.getPosition().y);
	}
	else if (m_situation == 1) {
		m_image.setPosition(m_image.getPosition().x - m_velocity, m_image.getPosition().y);
	}
}

void Organism::Render(sf::RenderWindow &window)
{
	sf::Text text;
	sf::Font font;
	font.loadFromFile("assets/fonts/MOTB.ttf");
	text.setString(m_name);
	text.setFont(font);
	text.setCharacterSize(50);
	text.setPosition(m_image.getPosition().x + text.getLocalBounds().width/2, m_image.getPosition().y-30);
	text.setFillColor(sf::Color::White);
	window.draw(m_image);
	window.draw(text);
}
