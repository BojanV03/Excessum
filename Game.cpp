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
	m_textures.Load("walk", "assets/images/walk.png");
	m_textures.Load("background", "assets/images/pozadina.png");
	m_textures.Load("knjiga", "assets/images/knjiga.png");

	m_fonts.Load("font1", "assets/fonts/MOTB.ttf");
	m_fonts.Load("rukopis", "assets/fonts/Sixteen_secodns.otf");
	m_fonts.Load("botovi", "assets/fonts/RoyalCrescentDemo.otf");

	m_currentState = new PlayState(this);

}
Game::~Game()
{
	delete m_currentState;
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
	m_currentState->Update(dt);
}

void Game::Render()
{
	m_window.clear();
	m_currentState->Render(m_window);
	m_window.display();
}
void Game::ProcessEvents()
{
	sf::Event event;

	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_window.close();
		}
	}
}
const TextureManager& Game::Textures() const
{
	return m_textures;
}
const FontManager& Game::Fonts() const
{
	return m_fonts;
}
void Game::ChangeState(State* state)
{
	delete m_currentState;
	m_currentState = state;
}
