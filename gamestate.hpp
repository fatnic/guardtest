#pragma once

#include "game.hpp"

class GameState
{
public:
  Game* game;

  virtual void draw() = 0;
  virtual void update(sf::Time dT) = 0;
  virtual void handleInput() = 0;
};
