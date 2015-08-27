#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

class GameState;

class Game
{
public:
    std::stack<GameState*> states;
    sf::RenderWindow window;

    void pushState(GameState* state);
    void popState();
    void changeState(GameState* state);
    GameState* peekState();

    void gameLoop();
    sf::Time dT;
    Game(sf::VideoMode videoMode, std::string windowTitle);
    ~Game();
};
