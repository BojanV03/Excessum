#pragma once


#ifdef __linux__
	#include <SFML/Graphics.hpp>
  #include "Consts.h"
	#include <iostream>
  #include <deque>
	#include "ResourceManager.h"
#elif defined _WIN32
	#include <SFML\Graphics.hpp>
	#include <iostream>
	#include "ResourceManager.h"
#endif

class Book
{
public:
   Book();
	 Book(const sf::Texture& texture);
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

private:
  sf::Sprite m_sprite;
  sf::Sprite m_skullSprite;
  unsigned m_score;
  float m_hp;
	std::deque<std::string> m_imena;
};
