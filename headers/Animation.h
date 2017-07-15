#pragma once
#include <SFML/Graphics.hpp>
enum Direction
{
  Right = 0,
  Left = 1
};
class Animation
{
public:
  
  Animation(const sf::Texture&, int x, int y, int width, int height, int num, float time);

  void Update();
  void Render(sf::RenderWindow& window);
private:
  sf::Clock m_clock;
  sf::IntRect m_imgSelector;
  sf::Sprite m_spriteSheet;

  float m_time;
  int m_num;
  int m_width;
};
