#ifndef GUARD_HPP
#define GUARD_HPP

#include <vector>
#include "entity.hpp"

struct PatrolPoint
{
    sf::Vector2f point;
    sf::Vector2f lookTarget;
    int waitTime = 5;
};

class Guard : public Entity
{
public:
    Guard();
    enum class Mode { Guarding, Patrolling, Alerted, Searching, Idle };
    void init();
    void update(sf::Time dT);
    void addPatrolPoint(sf::Vector2f point, sf::Vector2f lookTarget);
    void addPatrolPoint(sf::Vector2f point, sf::Vector2f lookTarget, int waitTime);
    void setTarget(sf::Vector2f target);
private:
    void guard();
    void moveToTarget(sf::Time dT);
    bool atTarget(sf::Vector2f target);
    bool atPatrolPoint();
    void nextPatrolPoint();
    void setMode(Mode mode);
    bool _initialized;
    float _speed;
    sf::Clock _waitClock;
    Mode _currentMode;
    sf::Vector2f _target;
    PatrolPoint _patrolPoint;
    std::vector<PatrolPoint> _patrolPoints;
    std::vector<PatrolPoint>::iterator i_patrolPoints;
};

#endif // GUARD_HPP
