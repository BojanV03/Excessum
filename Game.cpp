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

	m_fonts.Load("font1", "assets/fonts/MOTB.ttf");

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
<<<<<<< HEAD
	m_currentState->Render(m_window);
=======
	m_animation->Render(m_window);
	for(auto i = people.begin(); i != people.end(); i++)
	{
		Organism *a = *i;
		a->Render(m_window);
		a->Move();
		if(a->m_image.getPosition().x > WIDTH*1.1 || a->m_image.getPosition().y + a->m_image.getLocalBounds().width < WIDTH*0.1)
		{
	//		people.erase(i);
	//		delete a;
		}
	}
>>>>>>> d92d9da8bc03edb6bc7bbbdb43a8bb428568c3cd
	m_window.display();
}
void Game::ProcessEvents()
{
	sf::Event event;

	if(std::rand()%1000 == 7)
	{
		Organism* a = new Organism(m_textures.Get("skull"));
		people.push_back(a);
	}
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_window.close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
		//	std::cout << "Spawned" << std::endl;
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
