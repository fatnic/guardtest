#pragma once

#include "gamestate.hpp"
#include <tmx/MapLoader.h>
#include <vector>
#include "guard.hpp"

class MainGame : public GameState
{
public:
    MainGame(Game* game);
    virtual void handleInput();
    virtual void update(sf::Time dT);
    virtual void draw();
private:
    tmx::MapLoader _mapLoader;
    void loadMap(std::string tmxfilename);
    Guard _guard;
};
