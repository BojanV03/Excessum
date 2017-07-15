#include "headers/Animation.h"

Animation::Animation(const sf::Texture& texture, int x, int y, int width, int height, int num, float time)
  :m_imgSelector(x, y, width, height), m_num(num), m_time(time), m_width(width)
{
  m_spriteSheet = sf::Sprite(texture, m_imgSelector);
  m_clock.restart();
}

void Animation::Update()
{
  if (m_clock.getElapsedTime().asSeconds() > m_time) {
    if (m_imgSelector.left == m_num * m_width - m_width) {
      m_imgSelector.left = 0;
    } else {
      m_imgSelector.left += m_width;
    }

    m_spriteSheet.setTextureRect(m_imgSelector);
    m_clock.restart();
  }
}
void Animation::Render(sf::RenderWindow& window)
{
  window.draw(m_spriteSheet);
}
