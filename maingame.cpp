#include "maingame.hpp"

MainGame::MainGame(Game* game)
    : _mapLoader("assets/")
    , _guard()
{
    this->game = game;
    loadMap("land");

    _guard.addPatrolPoint(sf::Vector2f(70.f, 70.f), sf::Vector2f(320.f,320.f), 3);
    _guard.addPatrolPoint(sf::Vector2f(90.f, 400.f), sf::Vector2f(320.f,320.f));
    _guard.addPatrolPoint(sf::Vector2f(500.f, 400.f), sf::Vector2f(320.f,320.f), 2);
    _guard.addPatrolPoint(sf::Vector2f(400.f, 60.f), sf::Vector2f(320.f,320.f), 10);
}

void MainGame::handleInput()
{
    sf::Event event;
    while(game->window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            game->window.close();
            break;
        }
    }
}

void MainGame::update(sf::Time dT)
{
    _guard.update(dT);
}

void MainGame::draw()
{
   game->window.draw(_mapLoader);
   game->window.draw(_guard);
   return;
}

void MainGame::loadMap(std::string tmxfilename)
{
    _mapLoader.Load(tmxfilename + ".tmx");
}
