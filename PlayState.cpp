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

  m_book = Book(p_game->Textures(), p_game->Fonts());
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

//  loadMusic("asdfasef", 1.5, 80, true);

}

sf::Music PlayState::loadMusic(std::string music_filename, float music_frequency, float music_volume, bool music_loop)
{
    sf::Music music;
    music.openFromFile("start_game.wav");
    // if(!music.openFromFile("start_game.wav"))
    // {
    //     std::cout << "ERROR" << std::endl;
    // }
    music.setPitch(music_frequency);
    music.setVolume(music_volume);
    music.setLoop(music_loop);
//music.play();
}

void PlayState::ResetGame()
{
  Clean();
  m_optionsAnimation = false;
  m_bookAnimation = false;
  m_peopleMoving = false;
  m_drawBook = false;
  m_drawMenu = true;
  m_menuActive = true;
  m_optionsX = 100;
  m_options[0].setFillColor(sf::Color::Black);
  m_options[1].setFillColor(sf::Color::Black);
  m_options[0].setPosition(m_optionsX, HEIGHT - 475);
  m_options[1].setPosition(m_optionsX, m_options[0].getPosition().y + OPTIONS_LINE_HEIGHT);

  m_badge = sf::Sprite(p_game->Textures().Get("bedz"));
  m_badge.scale(0.25, 0.25);
  m_badge.setPosition(m_options[0].getGlobalBounds().left + m_options[0].getGlobalBounds().width + 20, m_options[0].getGlobalBounds().top - 5);

  m_logo = sf::Sprite(p_game->Textures().Get("logo"));
  m_logo.scale(0.35, 0.35);
  m_logo.setPosition(WIDTH - m_logo.getGlobalBounds().width - 150, HEIGHT/2 - m_logo.getGlobalBounds().height/2 + 35);

  m_spawnTime = 2;
  m_selectedOption = 0;
  m_book.isPlaying = false;
  m_book.SetTime(185.9);
  m_clock.restart();
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
        AddExplosion("explosion", m_organisms[i]->GetAnimation().GetX()-30, m_organisms[i]->GetAnimation().GetY()-120);
        DeleteOrganism(i);
        m_book.KillPerson(str);
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
    m_book.LoseTime(5);
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
      m_logo.setPosition(m_logo.getPosition().x + OPTIONS_MOVE_STEP * dt * 0.5, m_logo.getPosition().y);
    }
  }
  if (m_bookAnimation) {
    // kod za izlazak knjige. Kad izadje, krece igra
    //m_bookAnimation = false;
    m_drawBook = true;
    m_book.SetY(m_book.GetY() - 200 *dt);
    // pomeram knjigu za 200 * dt na gore, kada dodje do vrednosti, stane
    if (m_book.GetY() <= HEIGHT-m_book.GetSprite().getGlobalBounds().height + 170) {
      m_bookAnimation = false;
      m_peopleMoving = true;
      m_book.isPlaying = true;
    }
    return ;
  }
  if (m_peopleMoving && m_drawBook) {
    m_book.Update(dt);
    if(m_book.GetTime() < 0)
    {
      ResetGame();
      return;
    }
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
        m_book.LoseTime(5);
      }
    }
    UpdateAnimations();

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
    RenderAnimations(window);
  }
  if (m_drawBook) {
    // iscrtavanje knjige
    m_book.Render(window);
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
    } else if (key == sf::Keyboard::Key::Space || key == sf::Keyboard::Key::Return) {
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
void PlayState::AddExplosion(const std::string resourceName, float x, float y)
{
  Animation *animation = new Animation(sf::Sprite(p_game->Textures().Get(resourceName)), 0, 0, 108, 201, 6, 0.05, RIGHT);
  animation->SetPosition(x, y);
  m_animations.push_back(animation);
}
void PlayState::UpdateAnimations()
{
  for (size_t i = 0; i < m_animations.size(); i++) {
    if (m_animations[i]->Update()) {
      RemoveAnimation(i);
    }
  }
}
void PlayState::RenderAnimations(sf::RenderWindow& window)
{
  for (size_t i = 0; i < m_animations.size(); i++) {
    m_animations[i]->Render(window);
  }
}
void PlayState::RemoveAnimation(size_t index)
{
  m_animations[index] = m_animations.back();
  m_animations.pop_back();
}
