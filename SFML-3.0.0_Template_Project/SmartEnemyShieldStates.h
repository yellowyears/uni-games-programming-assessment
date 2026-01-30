#include "SmartEnemyState.h"

class ShieldedState : public SmartEnemyState
{
public:
    ShieldedState(SmartEnemy& owner);
    SmartEnemyState* update(float dt, const sf::Vector2f& playerPos) override;
};

class UnshieldedState : public SmartEnemyState
{
public:
    UnshieldedState(SmartEnemy& owner);
    SmartEnemyState* update(float dt, const sf::Vector2f& playerPos) override;
};
