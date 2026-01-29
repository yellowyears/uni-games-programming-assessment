/************************************************Task A-v*************************************************************
Refactor to ensure const correctness
************************************************************************************************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include "Trail.h"
#include <vector>

class Projectile 
{
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float lifeTime;
    std::vector<std::unique_ptr<Trail>> trails;   /******************************************Task ii - use  std::unique_ptr for managing trail objects ***********************/
    float trailTimer = 0.f; 

public:
    Projectile(const sf::Vector2f& pos, const sf::Vector2f& vel)
        : velocity(vel), lifeTime(2.f)
    {
        shape.setRadius(3.f);
        shape.setOrigin(sf::Vector2f(3.f, 3.f));
        shape.setPosition(pos);
        shape.setFillColor(sf::Color::Yellow);
    }

    sf::Vector2f getPosition() const
    {
        return shape.getPosition();
    }

    void update(float dt) 
    {
        shape.move(velocity * dt);      //move projectile and update its lifetime
        lifeTime -= dt;

        trailTimer += dt;               //update trailtimer and create add create/store a pointer to a new trail object if appropriate
        if (trailTimer >= 0.05f) 
        {
            trailTimer = 0.f;
            trails.push_back(std::make_unique<Trail>(shape.getPosition(), 2.f));
        }

        for (auto it = trails.begin(); it != trails.end();)     //update trail objects and remove dead trail objects
        {
            (*it)->update(dt);
            if ((*it)->dead()) {
                it = trails.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    void draw(sf::RenderWindow& window) const
    {
        for (const auto& t : trails) {
            t->draw(window);
        }
        window.draw(shape);
    }

    bool shouldDestroy() const
    {
        return lifeTime < 0;
    }

    sf::FloatRect bounds() const
    {
        return shape.getGlobalBounds();
    }

    float getRadius() const
    {
        return shape.getRadius();
    }
};
