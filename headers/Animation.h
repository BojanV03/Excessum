#pragma once
#include <SFML/Graphics.hpp>
enum Direction
{
  RIGHT = 0,
  LEFT = 1
};
class Animation
{
public:

  Animation(const sf::Sprite& sprite, int x, int y, int width, int height, int num, float time, Direction direction);

  void SetPosition(int x, int y);
  void Update();
  void Render(sf::RenderWindow& window);

  int GetWidth() const;
  int GetHeight() const;

  int GetX() const;
  int GetY() const;
private:
  sf::Clock m_clock;
  sf::Sprite m_spriteSheet;

  float m_time;
  int m_num;
  int m_width, m_height;
  int m_imgX, m_imgY;
  int m_x, m_y;
  Direction m_direction;
};
