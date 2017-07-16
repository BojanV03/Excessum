#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourceManager.h"
#include "Consts.h"

class Game;

class State
{
public:
    virtual ~State();

    virtual void Update(float dt) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual void Keyboard(char key) = 0; // Metoda za input sa tastature
    virtual void Controller(sf::Keyboard::Key& key) = 0;
    //virtual void mouse(sf::Event::MouseButtonEvent& event) = 0; // Metoda za input sa tastature

protected:
    State(Game* game);
    Game* p_game;
};
