#pragma once

#include "Game.h"
#include "State.h"
#include "Organism.h"
#include <vector>

class PlayState : public State
{
public:
  PlayState(Game* game);
  ~PlayState();

  void Update(float dt);
  void Render(sf::RenderWindow& window);
  void Clean();
private:
  std::vector<sf::Text> m_options;
  float m_optionsX;
  sf::Sprite m_background;

  // objects
  std::vector<Organism*> m_organisms;

  // bools - logic
  bool m_optionsAnimation;
  bool m_bookAnimation;
  Book knjiga;

private:
  const int OPTIONS_MOVE_STEP = 400;
  const int OPTIONS_LINE_HEIGHT = 120;
  const int OPTIONS_FONT_SIZE = 90;

private:

};
