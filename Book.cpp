#ifdef __linux__
	#include "headers/Book.h"
#elif defined _WIN32
	#include "headers\Book.h"
#endif

Book::Book()
{

}
Book::Book(const TextureManager& textures, const FontManager& fonts)
{
	m_sprite.setTexture(textures.Get("knjiga"));
  m_names = std::deque<std::string>();
  m_sprite.setPosition(WIDTH/2 - m_sprite.getLocalBounds().width/2, HEIGHT-m_sprite.getLocalBounds().height);
  m_hp = 5;

	m_botovi = sf::Font(fonts.Get("botovi"));

  m_score = 0;
}

Book::~Book()
{

}

void Book::KillPerson(const std::string &ime)
{
  m_names.push_front(std::string(ime));

  if(m_names.size() >= 10)
  {
    m_names.pop_back();
  }
}

sf::Sprite& Book::GetSprite()
{
  return m_sprite;
}
void Book::SetSprite(const sf::Sprite& spr)
{
  m_sprite = spr;
}

unsigned Book::GetScore()
{
  return m_score;
}

void Book::SetScore(unsigned newScore)
{
  m_score = newScore;
}

void Book::AddToScore(unsigned n)
{
  m_score += n;
}

float Book::GetHp()
{
  return m_hp;
}

void Book::SetHp(float newHp)
{
  m_hp = newHp;
}

void Book::LoseHp(float ammount)
{
  m_hp -= ammount;
}

void Book::Render(sf::RenderWindow &window)
{
  int j = 0;
  window.draw(m_sprite);
//  window.draw(m_skullSprite);

  for(auto i = m_names.cbegin(); i != m_names.cend(); i++)
  {
    j++;
		sf::Text text;

    text.setString(*i);
    text.setFont(m_botovi);
    text.setCharacterSize(30);
    text.setPosition(WIDTH/2 - 15, HEIGHT-m_sprite.getLocalBounds().height + j*30);

    text.setFillColor(sf::Color::Black);
//    std::cout << "Renderujemo osobu " << *i;
    window.draw(text);
  }
}
