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
  ~Animation();

  void SetPosition(float x, float y);
  void Update();
  void Render(sf::RenderWindow& window);

  int GetWidth() const;
  int GetHeight() const;

  float GetX() const;
  float GetY() const;

  Direction GetDirection() const;
private:
  sf::Clock m_clock;
  sf::Sprite m_spriteSheet;

  float m_time;
  int m_num;
  int m_width, m_height;
  int m_imgX, m_imgY;
  float m_x, m_y;
  Direction m_direction;
};
