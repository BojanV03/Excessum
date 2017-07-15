#include "headers/Game.h"
#include "headers/Collision.h"
#include "headers/Organism.h"
#include <iostream>
#include <vector>

std::vector<Organism*> people;

sf::Time Game::FPS = sf::seconds(1.0f / 60.0f);

Game::Game()
	:m_window(sf::VideoMode(WIDTH, HEIGHT), "Sfml Template")
{
	m_textures.Load("book", "assets/images/knjiga.jpg");
	m_textures.Load("skull", "assets/images/Skull.png");
	m_textures.Load("walk", "assets/images/dragon.png");

	m_animation = new Animation(m_textures.Get("walk"), 0, 0, 100, 100, 5, 0.1);
}
Game::~Game()
{

}
void Game::Run()
{
	sf::Clock clock;
	sf::Time lastUpdate = sf::Time::Zero;

	while (m_window.isOpen()) {
		ProcessEvents();
		lastUpdate += clock.restart();
		while (lastUpdate > FPS) {
			lastUpdate -= FPS;
			ProcessEvents();
			Update(FPS.asSeconds());
		}
		Render();
	}
}
void Game::Update(float dt)
{
	m_animation->Update();
}

void Game::Render()
{
	m_window.clear();
	m_animation->Render(m_window);
	for(auto i = people.begin(); i != people.end(); i++)
	{
		Organism *a = *i;
		a->Render(m_window);
		a->Move();
	}
	m_window.display();
}
void Game::ProcessEvents()
{
	sf::Event event;

	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_window.close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			std::cout << "Spawned" << std::endl;
			Organism* a = new Organism(m_textures.Get("skull"));
			people.push_back(a);
		}
	}
}
