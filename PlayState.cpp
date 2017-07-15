#include "headers/PlayState.h"

PlayState::PlayState(Game* game)
  :State(game), m_optionsX(100)
{
  m_options.push_back(sf::Text("Start Game", p_game->Fonts().Get("font1"), OPTIONS_FONT_SIZE));
  m_options.push_back(sf::Text("Exit Game", p_game->Fonts().Get("font1"), OPTIONS_FONT_SIZE));

  m_options[0].setPosition(m_optionsX, HEIGHT - 500);
  m_options[1].setPosition(m_optionsX, m_options[0].getPosition().y + OPTIONS_LINE_HEIGHT);

  knjiga = Book(p_game->Textures(), p_game->Fonts());
  m_optionsAnimation = false;  m_background = sf::Sprite(p_game->Textures().Get("background"));

  m_spawnTime = 2;
  m_clock.restart();
}
PlayState::~PlayState()
{
  Clean();
}

void PlayState::Keyboard(char key)
{
  std::cout << key << std::endl;

  m_inputText.push_back(key);

  std::string str(m_inputText.begin(),m_inputText.end());

  bool isFound = false;

  int i = 0;
  for(auto it = m_organisms.begin(); it != m_organisms.end(); it++, i++)
  {
    if((*it)->GetName().find(str) == 0)
    {
      (*it)->SetRenderText((*it)->GetName().substr(str.size()));
      isFound = true;
      if((*it)->GetName().size() == str.size())
      {
        std::cout << "JEDNAKO " << i << "  "<<  m_organisms.size() << '\n';
        knjiga.KillPerson(str);
        DeleteOrganism(i);
        m_inputText.clear();
        return;
      }
    }
    else
    {
      (*it)->SetRenderText((*it)->GetName());
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
    if (m_optionsX + m_options[0].getLocalBounds().width < 0) {
      std::cout << "Kraj animacije" << std::endl;
      m_optionsAnimation = false;
      m_bookAnimation = true;
      return;
    }
    for (size_t i = 0; i < m_options.size(); i++) {
      m_options[i].setPosition(m_optionsX, m_options[i].getPosition().y);
      m_options[i].setPosition(m_optionsX, m_options[i].getPosition().y);
    }
  }
  if (m_bookAnimation) {
    // kod za izlazak knjige. Kad izadje, krece igra
    m_bookAnimation = false;
    //m_startGame = true;
    return ;
  }
  if (m_clock.getElapsedTime().asSeconds() > m_spawnTime) {
    // Ako je proteklo vise od spawnTime
    // dodaj novog
    AddPerson();

    // sortiranje zbog preklapanja
    std::sort(m_organisms.begin(), m_organisms.end(), [](const Organism* l, const Organism* r) {
      return l->GetAnimation().GetY() < r->GetAnimation().GetY();
    });
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
void PlayState::Render(sf::RenderWindow& window)
{
  window.draw(m_background);
  if (m_optionsAnimation) {
    for (auto it = m_options.cbegin(); it != m_options.cend(); it++) {
      window.draw(*it);
    }
  }
  for (auto it = m_organisms.begin(); it != m_organisms.end(); it++) {
    (*it)->Render(window);
  }
	knjiga.Render(window);
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
}
int PlayState::GetPersonIndex() const
{
  return rand()%(NUM_PERSONS-1 + 1) + 1;
}
void PlayState::AddPerson()
{
  int index = GetPersonIndex();
  std::string name("person" + std::to_string(index));
  m_organisms.push_back(new Organism(p_game->Textures().Get(name), p_game->Fonts().Get("botovi")));
}
