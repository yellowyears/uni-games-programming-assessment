#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include <vector>
#include <random>
class BaseEnemy 
{
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float maxSpeed;
    float minSpeed;
    float speed;

    BaseEnemy(const sf::Vector2f& pos, float size = 16.f)
        : velocity(0, 0), maxSpeed(60.f), minSpeed(20)
    {
        shape.setRadius(size);  //create enemy shape
        shape.setOrigin(sf::Vector2f(size, size));
        shape.setPosition(pos);
        shape.setFillColor(sf::Color(242, 100, 25));

        std::random_device rd;  //generate random speed
        std::mt19937 rng(rd());
        std::uniform_real_distribution<float> speedDist(minSpeed, maxSpeed);
        speed = speedDist(rng);
    }

    float getRadius() const
    {
        return (shape.getLocalBounds().size.x / 2);
    }

    void update(float dt, const sf::Vector2f& playerPos) 
    {
        sf::Vector2f dir = playerPos - shape.getPosition();
        dir = dir.normalized();
        velocity = dir * speed;
        shape.move(velocity * dt);  //move towards player
    }


    const sf::Vector2f& getPosition() const
    {
        return shape.getPosition();
    }

    void draw(sf::RenderWindow& window) const 
    {
        window.draw(shape);
    }

    const sf::FloatRect& bounds() const 
    {
        return shape.getGlobalBounds(); 
    }
};