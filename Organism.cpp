#include "headers/Organism.h"
#include <chrono>
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
	float razmera;
	razmera = 0.5 + ((1.0*y-HEIGHT/3)/HEIGHT)*(1.5);
	m_image.setScale(razmera, razmera);
	if(m_situation == 0)
	{
//		m_image.setPosition(10, 10);
		m_anim = new Animation(m_image, 0, 0, 102, 148, 6, 0.1, RIGHT);
		m_anim->SetPosition(-m_anim->GetWidth(), y);
		std::cout << "Levo" << '\n';
	}
	else
	{
//		m_image.setPosition(10, 10);
		m_anim = new Animation(m_image, 0, 0, 102, 148, 6, 0.1, LEFT);
		m_anim->SetPosition(WIDTH, y);
		std::cout << "DESNO" << '\n';
	}
	m_velocity = (rand() % (m_VEL_MAX-m_VEL_MIN))+m_VEL_MIN;
}

Organism::~Organism()
{
	delete m_anim;
}

void Organism::Update (float dt)
{		// Changing position of organism according to velocity in coordinate system

	if (m_situation == 0)
	{
		m_anim->SetPosition(m_anim->GetX() + m_velocity*dt, m_anim->GetY());
	}
	else if (m_situation == 1) {
		m_anim->SetPosition(m_anim->GetX() - m_velocity*dt, m_anim->GetY());
	}
	//m_anim->SetPosition(m_anim->GetX(), m_anim->GetY());
	m_anim->Update();
}

std::string& Organism::GetName()
{
	return m_name;
}
void Organism::Render(sf::RenderWindow &window)
{
	sf::Text text;
	sf::Font font;
	font.loadFromFile("assets/fonts/RoyalCrescentDemo.otf");
	text.setString(m_name);
	text.setFont(font);
	text.setCharacterSize(22);
	text.setOutlineColor(sf::Color::Black);
	//text.setOutlineThickness(2);
	text.setPosition(m_anim->GetX() + m_anim->GetWidth()/2 - text.getLocalBounds().width/2, m_anim->GetY()-text.getLocalBounds().height*2.0);

	text.setFillColor(sf::Color::White);
	window.draw(text);
	m_anim->Render(window);
}
