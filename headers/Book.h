#pragma once

#include <SFML/Graphics.hpp>
#include "Consts.h"
#include <iostream>
#include <deque>
#include "ResourceManager.h"


class Book
{
public:
   Book();
	 Book(const TextureManager& textures, const FontManager& fonts);
	~Book();

  void KillPerson(const std::string &ime);

  sf::Sprite& GetSprite();
  void SetSprite(const sf::Sprite& spr);
  void Update(float dt);

  void SetTexture();

  unsigned GetScore();
  void SetScore(unsigned n);
  void AddToScore(unsigned n);

  float GetTime();
  void SetTime(float newTime);
  void LoseTime(float ammount);

  void Render(sf::RenderWindow &window);

  sf::Sprite& GetSkull();

  void SetY(float y);
  float GetY() const;

private:
  sf::Sprite m_sprite;
  sf::Sprite m_skull;
  sf::Sprite m_hourglass;
  sf::Font m_botovi;
  sf::Font m_rukopis;
  sf::Font m_stats;
  unsigned m_score;
  float m_time;
  int m_kills;
	std::deque<std::string> m_names;
};
