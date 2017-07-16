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

	isPlaying = false;

  m_names = std::deque<std::string>();
	// umesto HEIGHT-50 bilo je -> HEIGHT-m_sprite.getLocalBounds().height-75
  m_sprite.setPosition(WIDTH/2 - m_sprite.getLocalBounds().width/2-100, HEIGHT-50);
  m_time = 5;

	m_botovi = sf::Font(fonts.Get("botovi"));
	m_rukopis = sf::Font(fonts.Get("rukopis"));
	m_stats = sf::Font(fonts.Get("font1"));

	m_skull.setTexture(textures.Get("lobanja"));
	m_hourglass.setTexture(textures.Get("sat"));
	m_skull.setScale(1.5, 1.5);
	m_hourglass.setScale(1.5, 1.5);

	m_kills = 0;
	m_time = 180;
  m_score = 0;
}

Book::~Book()
{

}

void Book::KillPerson(const std::string &ime)
{
  m_names.push_front(std::string(ime));
	m_kills++;
	m_time += 2;
  if(m_names.size() >= 12)
  {
    m_names.pop_back();
  }
}

sf::Sprite& Book::GetSkull()
{
  return m_skull;
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

float Book::GetTime()
{
  return m_time;
}

void Book::SetTime(float newTime)
{
  m_time = newTime;
}

void Book::LoseTime(float ammount)
{
  m_time -= ammount;
}

void Book::Update(float dt)
{
	if(isPlaying)
		m_time -= dt;
}
void Book::Render(sf::RenderWindow &window)
{
  int j = 0;
/**************************/
	sf::Text tmpText;

	std::string time = "" + std::to_string(((int)m_time)/60) + "m " + std::to_string(((int)m_time)%60) + "s";

	tmpText.setString(time);
	tmpText.setFont(m_stats);
	tmpText.setFillColor(sf::Color::Black);
	tmpText.setCharacterSize(60);

	m_skull.setPosition(m_sprite.getPosition().x + 75, m_sprite.getPosition().y + 75);
	m_hourglass.setPosition(m_sprite.getPosition().x + 75, m_sprite.getPosition().y + 180);

	window.draw(m_sprite);
	window.draw(m_skull);
	window.draw(m_hourglass);
	tmpText.setPosition(m_sprite.getPosition().x + 150, m_sprite.getPosition().y + 183);
	window.draw(tmpText);
	tmpText.setString(std::to_string(m_kills));
	tmpText.setPosition(m_sprite.getPosition().x + 150, m_sprite.getPosition().y + 70);
	window.draw(tmpText);

/**************************/
//  window.draw(m_skullSprite);

  for(auto i = m_names.crbegin(); i != m_names.crend(); i++)
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
