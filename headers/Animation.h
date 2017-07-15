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

  Animation(const sf::Texture&, int x, int y, int width, int height, int num, float time, Direction direction);

  void Update();
  void Render(sf::RenderWindow& window);
private:
  sf::Clock m_clock;
  sf::Sprite m_spriteSheet;

  float m_time;
  int m_num;
  int m_width, m_height;
  int m_x, m_y;
  Direction m_direction;
};
