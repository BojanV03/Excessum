#pragma once


#ifdef __linux__
	#include <SFML/Graphics.hpp>
	#include <iostream>
	#include "Book.h"
	#include "ResourceManager.h"
	#include "Consts.h"
#elif defined _WIN32
	#include <SFML\Graphics.hpp>
	#include <iostream>
	#include "Book.h"
	#include "ResourceManager.h"
#endif

class Game
{
public:
	Game();
	~Game();

	void Run();
private:
	sf::RenderWindow m_window;
	static sf::Time FPS;
	TextureManager m_textures;
	sf::Sprite m_ship;
	Book knjiga;
private:
	void Update(float dt);
	void Render();
	void ProcessEvents();
};
