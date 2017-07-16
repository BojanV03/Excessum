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

  void SetTexture();

  unsigned GetScore();
  void SetScore(unsigned n);
  void AddToScore(unsigned n);

  float GetHp();
  void SetHp(float newHp);
  void LoseHp(float ammount);

  void Render(sf::RenderWindow &window);

  void SetY(float y);
  float GetY() const;
  
private:
  sf::Sprite m_sprite;
  sf::Font m_botovi;
  sf::Font m_rukopis;
  unsigned m_score;
  float m_hp;
	std::deque<std::string> m_names;
};
