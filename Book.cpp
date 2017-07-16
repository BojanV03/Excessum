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
	m_sprite.setScale(1.7, 1.7);

  m_names = std::deque<std::string>();
	// umesto HEIGHT-50 bilo je -> HEIGHT-m_sprite.getLocalBounds().height-75
  m_sprite.setPosition(WIDTH/2 - m_sprite.getLocalBounds().width/2-100, HEIGHT-50);
  m_hp = 5;

	m_botovi = sf::Font(fonts.Get("botovi"));
	m_rukopis = sf::Font(fonts.Get("rukopis"));

  m_score = 0;
}

Book::~Book()
{

}

void Book::KillPerson(const std::string &ime)
{
  m_names.push_front(std::string(ime));

  if(m_names.size() >= 15)
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
    text.setFont(m_rukopis);
    text.setCharacterSize(30);
    text.setPosition(WIDTH/2 + 10, HEIGHT-m_sprite.getLocalBounds().height + j*20 - 20);

    text.setFillColor(sf::Color::Black);
//    std::cout << "Renderujemo osobu " << *i;
    window.draw(text);
  }
}
void Book::SetY(float y)
{
	m_sprite.setPosition(m_sprite.getPosition().x, y);
}
float Book::GetY() const
{
	return m_sprite.getPosition().y;
}
