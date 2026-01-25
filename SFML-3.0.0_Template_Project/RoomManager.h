#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "BaseEnemy.h"
#include "SmartEnemy.h"
#include <vector>
#include <random>
class RoomManager 
{
public:
    std::vector<BaseEnemy*>& baseEnemies;
    std::vector<SmartEnemy*>& smartEnemies;
    sf::FloatRect bounds;
    int level;
    int difficultyMultiplier;

    RoomManager(const sf::FloatRect& bounds, std::vector<BaseEnemy*>& baseEnemies, std::vector<SmartEnemy*>& smartEnemies, int level) : 
        bounds(bounds), baseEnemies(baseEnemies), smartEnemies(smartEnemies), level(level), difficultyMultiplier(4)
    {
        spawnEnemies((1+level)*difficultyMultiplier);
    }

    /*********************************************Task B-iv *******************************************************************
    Refactor the RoomManager so that each enemy type is spawned by a dedicated instance of an EnemyFactory class.
    **********************************************************************************************************************/
    void spawnEnemies(int count) 
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_real_distribution<float> xdist(0, bounds.size.x);
        std::uniform_real_distribution<float> ydist(0, bounds.size.y);

        for (int i = 0; i < count; ++i) 
        {
            sf::Vector2f pos{ xdist(rng), ydist(rng) };
            baseEnemies.emplace_back(new BaseEnemy(pos));
        }

        for (int i = 0; i < count/2; ++i) 
        {
            sf::Vector2f pos{ xdist(rng), ydist(rng) };
            smartEnemies.emplace_back(new SmartEnemy(pos));
        }
    }

    void update(float dt, const sf::Vector2f& playerPos) 
    {
        for (auto& e : baseEnemies) 
        {
            e->update(dt, playerPos);
            sf::Vector2f p = e->shape.getPosition();
            if (p.x < 0) p.x = 0;
            if (p.y < 0) p.y = 0;
            if (p.x > 0 + bounds.size.x) p.x = 0 + bounds.size.x;
            if (p.y > 0 + bounds.size.y) p.y = 0 + bounds.size.y;
            e->shape.setPosition(p);
        }

        for (auto& e : smartEnemies) 
        {
            e->update(dt, playerPos);
            sf::Vector2f p = e->shape.getPosition();
            if (p.x < 0) p.x = 0;
            if (p.y < 0) p.y = 0;
            if (p.x > 0 + bounds.size.x) p.x = 0 + bounds.size.x;
            if (p.y > 0 + bounds.size.y) p.y = 0 + bounds.size.y;
            e->shape.setPosition(p);
        }
    }

    void draw(sf::RenderWindow& window) 
    {
        sf::RectangleShape border(sf::Vector2f(bounds.size.x, bounds.size.y));
        border.setPosition({ 0, 0 });
        border.setFillColor(sf::Color(20, 20, 30));
        window.draw(border);

        for (auto& e : baseEnemies) window.draw(e->shape);
        for (auto& e : smartEnemies) window.draw(e->shape);
    }
};