#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Book.h"
#include "ResourceManager.h"
#include "Consts.h"
#include "Animation.h"

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
	Animation *m_animation;

private:
	void Update(float dt);
	void Render();
	void ProcessEvents();
};
