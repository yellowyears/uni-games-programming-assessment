#pragma once

#include <SFML/Graphics.hpp>
class SmartEnemy;

class SmartEnemyState
{
protected:
    SmartEnemy& owner;
public:
    SmartEnemyState(SmartEnemy& owner) : owner(owner) {}
    virtual SmartEnemyState* update(float dt, const sf::Vector2f& playerPos) = 0;
};