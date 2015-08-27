#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stack>
#include <iostream>

#include "game.hpp"
#include "gamestate.hpp"


void Game::pushState(GameState *state)
{
    states.push(state);
    return;
}

void Game::popState()
{
    delete states.top();
    states.pop();
    return;
}

void Game::changeState(GameState *state)
{
    if(!states.empty()) popState();
    pushState(state);
    return;
}

GameState *Game::peekState()
{
    if(states.empty()) return nullptr;
    return states.top();
}

void Game::gameLoop()
{
    sf::Clock clock;
    while(window.isOpen())
    {
        sf::Time dT = clock.restart();
        if(peekState() == nullptr) continue;
        peekState()->handleInput();
        peekState()->update(dT);
        window.clear();
        peekState()->draw();
        window.display();
    }
}

Game::Game(sf::VideoMode videoMode, std::string windowTitle)
{
    window.create(videoMode, windowTitle);
    window.setFramerateLimit(60);
}

Game::~Game()
{
    while(!states.empty()) popState();
}
