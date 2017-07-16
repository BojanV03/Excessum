#include "headers/Animation.h"

Animation::Animation(const sf::Sprite& sprite, int x, int y, int width, int height, int num, float time, Direction direction)
  :m_imgX(x), m_imgY(y), m_num(num), m_time(time), m_width(width), m_height(height), m_direction(direction)
{
  m_spriteSheet = sprite;
  if (direction == RIGHT) {
    m_spriteSheet.setTextureRect(sf::IntRect(m_imgX, m_imgY, m_width, m_height));
    //m_spriteSheet = sf::Sprite(texture, sf::IntRect(m_imgX, m_imgY, m_width, m_height));
  } else {
    m_spriteSheet.setTextureRect(sf::IntRect(m_imgX + m_width, m_imgY, -m_width, m_height));
    //m_spriteSheet = sf::Sprite(texture, sf::IntRect(m_imgX + m_width, m_imgY, -m_width, m_height));
  }
  m_clock.restart();
}
Animation::~Animation()
{
}
int Animation::GetWidth() const
{
  return m_width;
}

int Animation::GetHeight() const
{
  return m_height;
}
float Animation::GetX() const { return m_x; }
float Animation::GetY() const { return m_y; }
void Animation::SetPosition(float x, float y)
{
  m_x = x;
  m_y = y;
}
void Animation::Update()
{
  if (m_clock.getElapsedTime().asSeconds() > m_time) {

    if (m_direction == LEFT) {
      m_spriteSheet.setTextureRect(sf::IntRect(m_imgX + m_width, m_imgY, -m_width, m_height));
    } else {
      m_spriteSheet.setTextureRect(sf::IntRect(m_imgX, m_imgY, m_width, m_height));
    }

    if (m_imgX == m_num * m_width - m_width) {
      m_imgX = 0;
    } else {
      m_imgX += m_width;
    }
    m_clock.restart();
  }
}
void Animation::Render(sf::RenderWindow& window)
{
  m_spriteSheet.setPosition(m_x, m_y);
  window.draw(m_spriteSheet);
}
Direction Animation::GetDirection() const
{
  return m_direction;
}
