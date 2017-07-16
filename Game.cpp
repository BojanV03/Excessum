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
	m_textures.Load("person1", "assets/images/person1.png"); // kauboj
	m_textures.Load("person2", "assets/images/person2.png"); // serif
	m_textures.Load("person3", "assets/images/person3.png"); // zena
	m_textures.Load("person4", "assets/images/person4.png"); // steampunk
	m_textures.Load("person5", "assets/images/person5.png"); // baba
	m_textures.Load("logo", "assets/images/logo.png"); // logo

	m_textures.Load("background", "assets/images/pozadina.png");
	m_textures.Load("knjiga", "assets/images/knjiga.png");
	m_textures.Load("bedz", "assets/images/bedz.png");

	m_fonts.Load("font1", "assets/fonts/OldTownRegular.ttf");
	m_fonts.Load("rukopis", "assets/fonts/Sixteen_secodns.otf");
	m_fonts.Load("botovi", "assets/fonts/OpenSans-CondLight.ttf");

	m_currentState = new PlayState(this);
	CURRENT_PERSON = 0;
	srand(time(NULL)); // Ovo mozda skinuti odavde
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
		else if(event.type == sf::Event::TextEntered)
		{
			if(event.text.unicode > 'a' && event.text.unicode < 'z' ||
				 event.text.unicode > 'A' && event.text.unicode < 'Z' || ' ')
			{
				m_currentState->Keyboard(static_cast<char>(event.text.unicode));
			}
		}
		else if (event.type == sf::Event::KeyPressed) {
			m_currentState->Controller(event.key.code);
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
