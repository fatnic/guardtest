#ifndef COMMON_HPP
#define COMMON_HPP

#include <SFML/Graphics.hpp>
#include <cassert>

namespace Common
{

float toDegree(float radian)
{
    return 180.f / 3.141592653589793238462643383f * radian;
}

sf::Vector2f direction(sf::Vector2f start, sf::Vector2f end)
{
    return start - end;
}

float length(sf::Vector2f vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f unitVector(sf::Vector2f vector)
{
    assert(vector != sf::Vector2f(0.f, 0.f));
    return vector / length(vector);
}

float rotation(sf::Vector2f origin, sf::Vector2f destination)
{
    sf::Vector2f dir = direction(origin, destination);
    return toDegree(std::atan2(dir.y, dir.x));
}

sf::Vector2f udirection(sf::Vector2f origin, sf::Vector2f target)
{
    return unitVector(direction(origin, target));
}

bool atTarget(sf::Vector2f origin, sf::Vector2f target)
{
    sf::CircleShape t(1.f);
    t.setOrigin(1.f, 1.f);
    t.setPosition(origin);
    if (t.getGlobalBounds().contains(target))
        return true;
    return false;
}

}

#endif // COMMON_HPP

