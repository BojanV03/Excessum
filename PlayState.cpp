#include "headers/PlayState.h"

PlayState::PlayState(Game* game)
  :State(game), m_optionsX(100)
{
  m_options.push_back(sf::Text("Start Game", p_game->Fonts().Get("font1"), OPTIONS_FONT_SIZE));
  m_options.push_back(sf::Text("Exit Game", p_game->Fonts().Get("font1"), OPTIONS_FONT_SIZE));
  m_options[0].setFillColor(sf::Color::Black);
  m_options[1].setFillColor(sf::Color::Black);
  m_options[0].setPosition(m_optionsX, HEIGHT - 475);
  m_options[1].setPosition(m_optionsX, m_options[0].getPosition().y + OPTIONS_LINE_HEIGHT);

  m_knjiga = Book(p_game->Textures(), p_game->Fonts());
  m_background = sf::Sprite(p_game->Textures().Get("background"));

  m_badge = sf::Sprite(p_game->Textures().Get("bedz"));
  m_badge.scale(0.25, 0.25);
  m_badge.setPosition(m_options[0].getGlobalBounds().left + m_options[0].getGlobalBounds().width + 20, m_options[0].getGlobalBounds().top - 5);

  m_logo = sf::Sprite(p_game->Textures().Get("logo"));
  m_logo.scale(0.35, 0.35);
  m_logo.setPosition(WIDTH - m_logo.getGlobalBounds().width - 150, HEIGHT/2 - m_logo.getGlobalBounds().height/2 + 35);

  m_spawnTime = 2;
  m_selectedOption = 0;
  m_clock.restart();

  m_optionsAnimation = false;
  m_bookAnimation = false;
  m_peopleMoving = false;
  m_drawBook = false;
  m_drawMenu = true;
  m_menuActive = true;
}
PlayState::~PlayState()
{
  Clean();
}

void PlayState::Keyboard(char key)
{
  //std::cout << key << std::endl;

  m_inputText.push_back(key);

  std::string str(m_inputText.begin(),m_inputText.end());

  bool isFound = false;

  int i = 0;
  for(auto it = m_organisms.begin(); it != m_organisms.end(); it++, i++)
  {
    if((*it)->GetName().find(str) == 0)
    {
      (*it)->SetRenderText((*it)->GetName().substr(str.size()));
      (*it)->SetColor(sf::Color::Red);
      isFound = true;
      if((*it)->GetName().size() == str.size())
      {
        //std::cout << "JEDNAKO " << i << "  "<<  m_organisms.size() << '\n';
        DeleteOrganism(i);
        m_knjiga.KillPerson(str);
        m_inputText.clear();
        return;
      }
    }
    else
    {
      (*it)->SetRenderText((*it)->GetName());
      (*it)->SetColor(sf::Color::White);
    }
  }
  if(!isFound)
  {
    m_inputText.clear();
  }
}

void PlayState::Update(float dt)
{
  if (m_optionsAnimation) {
    m_optionsX -= OPTIONS_MOVE_STEP * dt;
    if (m_badge.getGlobalBounds().left + m_badge.getGlobalBounds().width < 0) {

      m_optionsAnimation = false;
      m_drawMenu = false;
      m_bookAnimation = true;
      return;
    }
    for (size_t i = 0; i < m_options.size(); i++) {
      m_options[i].setPosition(m_optionsX, m_options[i].getPosition().y);
      m_options[i].setPosition(m_optionsX, m_options[i].getPosition().y);
      m_badge.setPosition(m_options[m_selectedOption].getGlobalBounds().left + m_options[m_selectedOption].getGlobalBounds().width + 20, m_badge.getPosition().y);
    }
  }
  if (m_bookAnimation) {
    // kod za izlazak knjige. Kad izadje, krece igra
    //m_bookAnimation = false;
    m_drawBook = true;
    m_knjiga.SetY(m_knjiga.GetY() - 200 *dt);
    // pomeram knjigu za 200 * dt na gore, kada dodje do vrednosti, stane
    if (m_knjiga.GetY() <= HEIGHT-m_knjiga.GetSprite().getGlobalBounds().height+100) {
      m_bookAnimation = false;
      m_peopleMoving = true;
    }
    return ;
  }
  if (m_peopleMoving && m_drawBook) {
    if (m_clock.getElapsedTime().asSeconds() > m_spawnTime) {
      // Ako je proteklo vise od spawnTime
      // dodaj novog
      CURRENT_PERSON++;
      AddPerson();

      // sortiranje zbog preklapanja
      SortOrganisms();
      m_clock.restart();
    }
    for (size_t i = 0; i < m_organisms.size(); i++) {
      m_organisms[i]->Update(dt);

      if ((m_organisms[i]->GetAnimation().GetX() > WIDTH &&
          m_organisms[i]->GetAnimation().GetDirection() == RIGHT) ||
          (m_organisms[i]->GetAnimation().GetX() + m_organisms[i]->GetAnimation().GetWidth() < 0 &&
           m_organisms[i]->GetAnimation().GetDirection() == LEFT))
      {
        // Izasao izvan ekrana
        DeleteOrganism(i);
      }
    }
  }
}
void PlayState::Render(sf::RenderWindow& window)
{
  window.draw(m_background);
  if (m_drawMenu) {
    // iscrtavanje menija i logoa
    for (auto it = m_options.cbegin(); it != m_options.cend(); it++) {
      window.draw(*it);
    }
    window.draw(m_badge);
    window.draw(m_logo);
  }
  if (m_peopleMoving) {
    // iscrtavnje ljudi
    for (auto it = m_organisms.begin(); it != m_organisms.end(); it++) {
      (*it)->Render(window);
    }
  }
  if (m_drawBook) {
    // iscrtavanje knjige
    m_knjiga.Render(window);
  }
}
void PlayState::Clean()
{
  // Brisanje organizama
  for (size_t i = 0; i < m_organisms.size(); i++) {
    DeleteOrganism(i);
  }
}
void PlayState::DeleteOrganism(size_t indeks)
{
  m_organisms[indeks] = m_organisms.back();
  m_organisms.pop_back();
  SortOrganisms();
}
int PlayState::GetPersonIndex() const
{
  return rand()%(NUM_PERSONS-1 + 1) + 1;
}
void PlayState::AddPerson()
{
  int index = GetPersonIndex();
  std::string name("person" + std::to_string(index));
  m_organisms.push_back(new Organism(p_game->Textures().Get(name), p_game->Fonts().Get("botovi"), m_organisms));
}
void PlayState::Controller(sf::Keyboard::Key& key)
{
  if (m_menuActive) {
    if (key == sf::Keyboard::Key::S || key == sf::Keyboard::Key::Down) {
      m_selectedOption++;
      if (m_selectedOption == m_options.size()) {
        m_selectedOption = 0;
      }
    } else if (key == sf::Keyboard::Key::W || key == sf::Keyboard::Key::Up) {
      m_selectedOption--;
      if (m_selectedOption < 0) {
        m_selectedOption = m_options.size() - 1;
      }
    } else if (key == sf::Keyboard::Key::Space) {
      if (m_selectedOption == m_options.size()-1) {
        Clean();
        exit(EXIT_SUCCESS);
      }
      if (m_selectedOption == 0) {
        m_menuActive = false;
        m_optionsAnimation = true;
      }
    }
    sf::Text option = m_options[m_selectedOption];
    m_badge.setPosition(option.getGlobalBounds().left + option.getGlobalBounds().width + 20, option.getGlobalBounds().top);

  }
}
void PlayState::SortOrganisms()
{
  std::sort(m_organisms.begin(), m_organisms.end(), [](const Organism* l, const Organism* r) {
    return l->GetAnimation().GetY() < r->GetAnimation().GetY();
  });
}
