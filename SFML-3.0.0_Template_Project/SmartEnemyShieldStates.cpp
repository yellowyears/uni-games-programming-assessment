#include "SmartEnemyShieldStates.h"
#include "SmartEnemy.h"


ShieldedState::ShieldedState(SmartEnemy& owner) : SmartEnemyState(owner)
{

}

SmartEnemyState* ShieldedState::update(float dt, const sf::Vector2f& playerPos)
{
    //sf::Vector2f dir = playerPos - shape.getPosition();
    //dir = dir.normalized();
    //velocity = dir * speed;
    //shape.move(velocity * dt);

    return nullptr;
}

UnshieldedState::UnshieldedState(SmartEnemy& owner) : SmartEnemyState(owner)
{

}

SmartEnemyState* UnshieldedState::update(float dt, const sf::Vector2f& playerPos)
{
    //owner.timeAccumulator += dt;  // wavy movement when shield is destroyed
    //sf::Vector2f dir = playerPos - shape.getPosition();
    //float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    //if (len != 0) dir /= len;

    //sf::Vector2f perp(-dir.y, dir.x);

    //float waveAmplitude = 180.f;
    //float waveFrequency = 1.f;
    //float offset = std::sin(timeAccumulator * waveFrequency) * waveAmplitude;

    //sf::Vector2f finalDir = dir * speed + perp * offset;

    //shape.move(finalDir * dt);

    return nullptr;
}