#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Book.h"
#include "ResourceManager.h"
#include "Consts.h"

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

	Book m_book;
private:
	void Update(float dt);
	void Render();
	void ProcessEvents();
};
