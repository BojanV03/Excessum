#include "headers/PlayState.h"

PlayState::PlayState(Game* game)
  :State(game), m_optionsX(100)
{
  m_options.push_back(sf::Text("Start Game", p_game->Fonts().Get("font1"), OPTIONS_FONT_SIZE));
  m_options.push_back(sf::Text("Exit Game", p_game->Fonts().Get("font1"), OPTIONS_FONT_SIZE));

  m_options[0].setPosition(m_optionsX, HEIGHT - 500);
  m_options[1].setPosition(m_optionsX, m_options[0].getPosition().y + OPTIONS_LINE_HEIGHT);

  m_optionsAnimation = true;
}
PlayState::~PlayState()
{
}
void PlayState::Update(float dt)
{
  if (m_optionsAnimation) {
    m_optionsX -= OPTIONS_MOVE_STEP * dt;
    if (m_optionsX + m_options[0].getLocalBounds().width < 0) {
      std::cout << "Kraj animacije" << std::endl;
      m_optionsAnimation = false;
      m_bookAnimation = true;
      return;
    }
    for (size_t i = 0; i < m_options.size(); i++) {
      m_options[i].setPosition(m_optionsX, m_options[i].getPosition().y);
      m_options[i].setPosition(m_optionsX, m_options[i].getPosition().y);
    }
  }
  if (m_bookAnimation) {
    // kod za izlazak knjige. Kad izadje, krece igra
    m_bookAnimation = false;
    //m_startGame = true;
    return ;
  }
}
void PlayState::Render(sf::RenderWindow& window)
{
  for (auto it = m_options.cbegin(); it != m_options.cend(); it++) {
    window.draw(*it);
  }
}
