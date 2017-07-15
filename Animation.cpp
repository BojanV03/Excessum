#include "headers/Animation.h"

Animation::Animation(const sf::Sprite& sprite, int x, int y, int width, int height, int num, float time, Direction direction)
  :m_x(x), m_y(y), m_num(num), m_time(time), m_width(width), m_height(height), m_direction(direction)
{
  m_spriteSheet = sprite;
  if (direction == RIGHT) {
    m_spriteSheet.setTextureRect(sf::IntRect(m_x, m_y, m_width, m_height));
    //m_spriteSheet = sf::Sprite(texture, sf::IntRect(m_x, m_y, m_width, m_height));
  } else {
    m_spriteSheet.setTextureRect(sf::IntRect(m_x + m_width, m_y, -m_width, m_height));
    //m_spriteSheet = sf::Sprite(texture, sf::IntRect(m_x + m_width, m_y, -m_width, m_height));
  }
  m_clock.restart();
}

void Animation::Update()
{
  if (m_clock.getElapsedTime().asSeconds() > m_time) {

    if (m_direction == LEFT) {
      m_spriteSheet.setTextureRect(sf::IntRect(m_x + m_width, m_y, -m_width, m_height));
    } else {
      m_spriteSheet.setTextureRect(sf::IntRect(m_x, m_y, m_width, m_height));
    }

    if (m_x == m_num * m_width - m_width) {
      m_x = 0;
    } else {
      m_x += m_width;
    }
    m_clock.restart();
  }
}
void Animation::Render(sf::RenderWindow& window)
{
  window.draw(m_spriteSheet);
}
