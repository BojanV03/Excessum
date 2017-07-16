#include "headers/Organism.h"
#include <chrono>
#include <iostream>

#define EASY_SIZE 100
#define MEDIUM_SIZE 149
#define HARD_SIZE 111

Organism::Organism()
{
}

Organism::Organism(const sf::Texture &a, const sf::Font& font)
{
	m_image.setTexture(a);
	m_situation = rand() % 2;
	std::string firstName, lastName;
	int y = (rand() % (int)(HEIGHT/6)) + HEIGHT/3;

	if(CURRENT_PERSON < 50)
	{
		std::cout << "Easy Name #" << CURRENT_PERSON << ": ";
		std::ifstream input("assets/data/easy.txt");
		int name = rand() % EASY_SIZE;

		for(int i = 0; i < name; i++)
		{
			input >> firstName >> lastName;
		}
	}
	else if(CURRENT_PERSON < 100)
	{
		std::ifstream input("assets/data/medium.txt");
		int name = rand() % MEDIUM_SIZE;
		std::cout << "Medium Name #" << CURRENT_PERSON << " with ID" << name << ": ";

		for(int i = 0; i < name; i++)
		{
			input >> firstName >> lastName;
		}
	}
	else if(CURRENT_PERSON < 150)
	{
		std::ifstream input("assets/data/hard.txt");
		int name = (rand() % HARD_SIZE);
		std::cout << "Hard Name #" << CURRENT_PERSON << " with ID" << name << " :";

		for(int i = 0; i < name; i++)
		{
			input >> firstName >> lastName;
		}
	}

	m_name = std::string(firstName + " " + lastName);

	float razmera;
	razmera = 0.5 + ((1.0*y-HEIGHT/3)/HEIGHT)*(1.5);
	m_image.setScale(razmera, razmera);
	m_renderText.setString(m_name);
	if(m_situation == 0)
	{
//		m_image.setPosition(10, 10);
		m_anim = new Animation(m_image, 0, 0, 108, 201, 5, 0.1*razmera, RIGHT);
		m_anim->SetPosition(-m_anim->GetWidth(), y);
	}
	else
	{
//		m_image.setPosition(10, 10);
		m_anim = new Animation(m_image, 0, 0, 108, 201, 5, 0.1*razmera, LEFT);
		m_anim->SetPosition(WIDTH, y);
	}
	m_velocity = 100*razmera;
	m_font = sf::Font(font);
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

void Organism::SetRenderText(const std::string& s)
{
	m_renderText.setString(s);
}

const Animation& Organism::GetAnimation() const
{
	return *m_anim;
}

void Organism::SetColor(sf::Color c)
{
	m_textColor = sf::Color(c);
}
void Organism::Render(sf::RenderWindow &window)
{
	m_renderText.setFont(m_font);
	m_renderText.setCharacterSize(30);
	m_renderText.setPosition(m_anim->GetX() + m_anim->GetWidth()/2 - m_renderText.getGlobalBounds().width/2, m_anim->GetY()-m_renderText.getCharacterSize()*1.2);

	m_renderText.setFillColor(m_textColor);
	window.draw(m_renderText);
	m_anim->Render(window);
}
