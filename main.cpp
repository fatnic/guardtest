#include "game.hpp"
#include "maingame.hpp"

int main()
{
    Game game(sf::VideoMode(640,640), "GameWindow");
    game.pushState(new MainGame(&game));
    game.gameLoop();
}


