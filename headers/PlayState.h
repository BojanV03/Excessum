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
  int GetPersonIndex() const;
  void AddPerson();
  void Keyboard(char key);
  void Controller(sf::Keyboard::Key& key); // za kretanje kroz meni
private:
  std::vector<sf::Text> m_options;

  sf::Sprite m_background;
  sf::Clock m_clock;

  float m_optionsX;
  float m_spawnTime;

  // objects
  std::vector<Organism*> m_organisms;
  std::vector<char> m_inputText;
  Book m_knjiga;

  // bools - logic
  bool m_optionsAnimation;
  bool m_bookAnimation;
  bool m_peopleMoving;
  bool m_drawMenu;
  bool m_drawBook;


private:
  const int OPTIONS_MOVE_STEP = 400;
  const int OPTIONS_LINE_HEIGHT = 120;
  const int OPTIONS_FONT_SIZE = 90;

private:
  void DeleteOrganism(size_t indeks);
  void SortOrganisms();
};
