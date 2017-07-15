#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Book.h"
#include "ResourceManager.h"
#include "Consts.h"
#include "Animation.h"
#include "PlayState.h"
#include "State.h"

class Game
{
public:
	Game();
	~Game();

	void Run();
	const TextureManager& Textures() const;
	const FontManager& Fonts() const;
private:
	sf::RenderWindow m_window;
	static sf::Time FPS;

	TextureManager m_textures;
	FontManager m_fonts;

	State* m_currentState;
private:
	void Update(float dt);
	void Render();
	void ProcessEvents();
	void ChangeState(State* state);
};
