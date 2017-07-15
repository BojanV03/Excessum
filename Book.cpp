#ifdef __linux__
	#include "headers/Book.h"
#elif defined _WIN32
	#include "headers\Book.h"
#endif

Book::Book()
{

}
Book::Book(const sf::Texture& texture)
  : m_sprite(texture)
{
  m_imena = std::deque<std::string>();
  m_sprite.setPosition(WIDTH/2 - m_sprite.getLocalBounds().width/2, HEIGHT-m_sprite.getLocalBounds().height);
  m_hp = 5;

  sf::Texture skullTexture;
  skullTexture.loadFromFile("images/Skull.png");
  m_skullSprite = sf::Sprite(skullTexture);

  m_score = 0;
}

Book::~Book()
{

}

void Book::KillPerson(const std::string &ime)
{
  m_imena.push_front(std::string(ime));

  if(m_imena.size() >= 10)
  {
    m_imena.pop_back();
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
  window.draw(m_skullSprite);

  for(auto i = m_imena.cbegin(); i != m_imena.cend(); i++)
  {
    sf::Text text;
    sf::Font font;
    j++;
    font.loadFromFile("MOTB.ttf");
    text.setString(*i);
    text.setFont(font);
    text.setCharacterSize(50);
    text.setPosition(WIDTH/2 + 30, HEIGHT-m_sprite.getLocalBounds().height + j*30);
    text.setFillColor(sf::Color::Black);
    std::cout << "Renderujemo osobu " << *i;
    window.draw(text);
  }
}
