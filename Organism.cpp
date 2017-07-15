#include "headers/Organism.h"
#include <iostream>

Organism::Organism()
{

}

Organism::Organism(const sf::Texture &a)
{
	srand(time(NULL));
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
//		m_image.setPosition(10, 10);
		m_image.setPosition(-m_anim->getWidth(), y);
		m_anim = new Animation(m_image, 0, 0, 102, 148, 6, 0.1, RIGHT);
		std::cout << "DESNO" << '\n';
	}
	else
	{
//		m_image.setPosition(10, 10);
		m_image.setPosition(WIDTH, y);
		m_anim = new Animation(m_image, 0, 0, 102, 148, 6, 0.1, LEFT);
		std::cout << "DESNO" << '\n';
	}
	m_velocity = (rand() % (m_VEL_MAX-m_VEL_MIN))+m_VEL_MIN;
	float razmera;
	razmera = 0.5 + ((1.0*y-HEIGHT/3)/HEIGHT)*(1.5);
	m_image.setScale(razmera, razmera);
}

void Organism::Update ()
{		// Changing position of organism according to velocity in coordinate system
	
	if (m_situation == 0)
	{
		m_image.setPosition(m_image.getPosition().x + m_velocity, m_image.getPosition().y);
	}
	else if (m_situation == 1) {
		m_image.setPosition(m_image.getPosition().x - m_velocity, m_image.getPosition().y);
	}
	m_anim->setPosition(m_image.getPosition().x, m_image.getPosition().y);
	m_anim->Update();
}

void Organism::Render(sf::RenderWindow &window)
{
	sf::Text text;
	sf::Font font;
	font.loadFromFile("assets/fonts/MOTB.ttf");
	text.setString(m_name);
	text.setFont(font);
	text.setCharacterSize(50);
	text.setPosition(m_image.getPosition().x + m_anim->getWidth()/2 - text.getLocalBounds().width/2, m_image.getPosition().y-text.getLocalBounds().height*1.1);
	text.setFillColor(sf::Color::White);
	window.draw(text);
	m_anim->Render(window);
}
