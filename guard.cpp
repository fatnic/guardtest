#include "guard.hpp"
#include <iostream>
#include "common.hpp"
#include <math.h>
#include <algorithm>
#include <cassert>

Guard::Guard()
    : _currentMode(Mode::Idle)
    , _target(0.f, 0.f)
    , _speed(2.f)
    , _initialized(false)
{
    this->load("assets/guard.png");
    this->setOrigin(this->getGlobalBounds().width/2, this->getGlobalBounds().height/2);
    this->setScale(0.5f, 0.5f);
}

void Guard::init()
{
    _initialized = true;

    assert(!_patrolPoints.empty());
    this->setPosition(_patrolPoints.front().point);

    i_patrolPoints = _patrolPoints.begin();
    _patrolPoint = *i_patrolPoints;
    _waitClock.restart();
    setMode(Mode::Guarding);
}

void Guard::update(sf::Time dT)
{
    if(!_initialized)
        init();

    switch(_currentMode)
    {
    case Mode::Idle:
        break;
    case Mode::Patrolling:
        if(!atPatrolPoint())
        {
            moveToTarget(dT);
        }
        else
        {
            _waitClock.restart();
            setMode(Mode::Guarding);
        }
        break;
    case Mode::Guarding:
        guard();
        break;
    case Mode::Alerted:
        // TODO: Go towards alerted target
        // search
        break;
    case Mode::Searching:
        // TODO: Move around a radius
        // if nothing player not found after n seconds return to nearest patrol point
        break;
    }
}

void Guard::addPatrolPoint(sf::Vector2f point, sf::Vector2f lookTarget)
{
    PatrolPoint pp;
    pp.point = point;
    pp.lookTarget = lookTarget;
    _patrolPoints.push_back(pp);
    _currentMode = Mode::Patrolling;
}

void Guard::addPatrolPoint(sf::Vector2f point, sf::Vector2f lookTarget, int waitTime)
{
    PatrolPoint pp;
    pp.point = point;
    pp.lookTarget = lookTarget;
    pp.waitTime = waitTime;
    _patrolPoints.push_back(pp);
    _currentMode = Mode::Patrolling;
}

void Guard::setTarget(sf::Vector2f target)
{
    _target = target;
}

void Guard::guard()
{
    if(_waitClock.getElapsedTime().asSeconds() >= _patrolPoint.waitTime)
    {
        _waitClock.restart();
        nextPatrolPoint();
        setMode(Mode::Patrolling);
    }

    // Add some sort of easing into this
    sf::Vector2f target = Common::direction(_patrolPoint.lookTarget, this->getPosition());
    sf::Vector2f velocity = Common::unitVector(sf::Vector2f(target.x, target.y));
    float angle = std::atan2(velocity.y, velocity.x);

    setRotation(Common::toDegree(angle)+90);

}

void Guard::moveToTarget(sf::Time dT)
{
    sf::Vector2f target = Common::direction(_target, this->getPosition());
    sf::Vector2f velocity = Common::unitVector(sf::Vector2f(target.x + dT.asSeconds(), target.y + dT.asSeconds()));
    float angle = std::atan2(velocity.y, velocity.x);

    velocity *= _speed;

    setRotation(Common::toDegree(angle)+90);
    move(velocity);
}

bool Guard::atPatrolPoint()
{
    if(Common::atTarget(this->getPosition(), _patrolPoint.point))
        return true;
    return false;
}

void Guard::nextPatrolPoint()
{
    if(i_patrolPoints == _patrolPoints.end() - 1)
    {
        std::reverse(_patrolPoints.begin(), _patrolPoints.end());
        i_patrolPoints = _patrolPoints.begin() + 1;
    }
    else
    {
        i_patrolPoints++;
    }
    _patrolPoint = *i_patrolPoints;
    setTarget(_patrolPoint.point);
}

void Guard::setMode(Guard::Mode mode)
{
    _currentMode = mode;
}


