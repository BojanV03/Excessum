#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <algorithm>
#include "Book.h"
#include "Consts.h"
#include "PlayState.h"

class KeyboardInput
{
public:
	KeyboardInput();
	~KeyboardInput();

private:
  std::vector<char> m_typed;
};
