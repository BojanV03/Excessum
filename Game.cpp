#ifdef __linux__
	#include "headers/Game.h"
	#include "headers/Collision.h"
	#include <iostream>
#elif defined _WIN32
	#include "headers\Game.h"
	#include "headers\Collision.h"
#endif


sf::Time Game::FPS = sf::seconds(1.0f / 60.0f);

Game::Game()
	:m_window(sf::VideoMode(WIDTH, HEIGHT), "Sfml Template")
{
	m_textures.Load("ship", "images/knjiga.jpg");

	knjiga = Book(m_textures.Get("ship"));
	m_ship.setTexture(m_textures.Get("ship"));
	m_ship.setPosition(200, 200);

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

}

void Game::Render()
{
	m_window.clear();

	knjiga.Render(m_window);

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
			std::string s;
			std::cin >> s;
			knjiga.KillPerson(s);
			std::cout << "Ubijena osoba " << s << std::endl;
		}
	}
}
