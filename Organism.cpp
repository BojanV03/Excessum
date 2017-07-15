#include "headers/Organism.h"

Organism::Organism()
{

}

Organism::Organism(const sf::Texture &a)
{
	m_image.setTexture(a);
	m_situation = rand() % 2;
	int y = (rand() % (int)(HEIGHT/3)) + HEIGHT/3;
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
	razmera = 0.5 + ((1.0*y-HEIGHT/3)/HEIGHT)*(1.5);
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
	window.draw(m_image);
}
