#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include <vector>
#include <random>

class SmartEnemy 
{
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float speed;
    bool shielded;
    float timeAccumulator;
    float minSpeed, maxSpeed;

    SmartEnemy(const sf::Vector2f& pos, float size = 16.f)
        : velocity(0, 0), speed(20.f), shielded(true), timeAccumulator(0), minSpeed(20), maxSpeed(60)
    {
        shape.setRadius(size);
        shape.setOrigin(sf::Vector2f(size, size));
        shape.setPosition(pos);
        shape.setFillColor(sf::Color(242, 25, 25));
        shape.setOutlineThickness(4);
        shape.setOutlineColor(sf::Color(63, 142, 252));

        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_real_distribution<float> speedDist(minSpeed, maxSpeed);

        speed = speedDist(rng);
    }

    float getRadius() const
    {
        return (shape.getLocalBounds().size.x / 2);
    }

    void removeShield()
    {
        shielded = false;
        shape.setOutlineThickness(0);
    }

    bool isShielded() const
    {
        return shielded;
    }

    void update(float dt, const sf::Vector2f& playerPos) 
    {
        /***********************************************Task B-ii ********************************************************************
        Refactor this using the State Pattern so that shielded and unshielded behaviours are encapsulated in separate states
        **************************************************************************************************************************/

        if (shielded)   //simple movement towards player
        {
            sf::Vector2f dir = playerPos - shape.getPosition();
            dir = dir.normalized();
            velocity = dir * speed;
            shape.move(velocity * dt); 
        }
        else
        {
            timeAccumulator += dt;  // wavy movement when shield is destroyed
            sf::Vector2f dir = playerPos - shape.getPosition();
            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            if (len != 0) dir /= len;

            sf::Vector2f perp(-dir.y, dir.x);

            float waveAmplitude = 180.f;   
            float waveFrequency = 1.f;    
            float offset = std::sin(timeAccumulator * waveFrequency) * waveAmplitude;

            sf::Vector2f finalDir = dir * speed + perp * offset;

            shape.move(finalDir * dt);
        }
    }


    const sf::Vector2f& getPosition() const
    {
        return shape.getPosition();
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(shape);
    }

    const sf::FloatRect& bounds() const
    { 
        return shape.getGlobalBounds(); 
    }
};