#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include <vector>
#include <random>
#include <iostream>

class Player 
{
    sf::ConvexShape ship;
    sf::Vector2f velocity;
    float thrustPower;
    float maxSpeed;
    float shotCooldown;
    float shotTimer;
    bool shieldActive;
    sf::Clock shieldTimer;
    sf::Clock shieldCooldown;
    float projectileSpeed;
    float velScaler;
    bool boostUnlocked;
    std::vector<Projectile*>& projectiles;

public:
    Player(std::vector<Projectile*>& projectiles, const sf::Vector2f& pos)
        : velocity(0, 0), thrustPower(240.f), maxSpeed(350.f), shotCooldown(0.22f), shotTimer(0.f), projectiles(projectiles),
       boostUnlocked(false), shieldActive(false), projectileSpeed(520), velScaler(0.2)
    {
        ship.setPointCount(3);
        ship.setPoint(0, { 24.f, 0.f });        // nose to the right
        ship.setPoint(1, { -24.f, -24.f });     // back top
        ship.setPoint(2, { -24.f,  24.f });     // back bottom
        ship.setFillColor(sf::Color::Cyan);
        ship.setOutlineColor(sf::Color::Black);
        ship.setOutlineThickness(1.f);
        ship.setPosition(pos);
        ship.setOrigin(sf::Vector2f(0, 0));
        ship.setOutlineColor(sf::Color::White);
        shieldCooldown.start();

    }

    void update(float dt) 
    {
        /*************************************** Task B-i ********************************************************
        Refactor this class using the component pattern so that these 3 behaviours can be added to the ship as components
        * ********************************************************************************************************/

        /************************************* Movement *********************************/
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) ship.rotate(sf::degrees(- maxSpeed * dt));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) ship.rotate(sf::degrees(maxSpeed * dt));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) 
        {
            sf::Vector2f forward{ std::cos(float(ship.getRotation().asRadians())), std::sin(float(ship.getRotation().asRadians()))};
            velocity += forward * thrustPower * dt;
        }
       
        float sp = velocity.length();
        if (sp > maxSpeed) velocity = velocity.normalized() * maxSpeed;
        velocity *= (1.0f - std::min(dt * 2.5f, 1.0f)); // simple damping
        ship.move(velocity * dt);

        /************************************* Shooting *********************************/
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) shoot();
        shotTimer -= dt;
        for (const auto& p : projectiles) 
        {
            p->update(dt);
        }

        for (auto it = projectiles.begin(); it != projectiles.end(); )
        {
            if ((*it)->shouldDestroy()) 
            {
                it = projectiles.erase(it);
            }
            else 
            {
                ++it;
            }
        }

        /************************************* Shielding *********************************/
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && !shieldActive && shieldCooldown.getElapsedTime().asSeconds()>2)
        {
            shieldActive = true;
            ship.setOutlineThickness(4);
            shieldTimer.restart();
        }
        
        if (shieldActive && shieldTimer.getElapsedTime().asSeconds() > 3)
        {
            shieldActive = false;
            ship.setOutlineThickness(0);
            shieldCooldown.restart();
        }
    }

    bool canShoot() const
    { 
        return shotTimer <= 0.f; 
    }

    const sf::FloatRect& getBoundaries() const
    {
        return ship.getGlobalBounds();
    }

    const sf::Vector2f& getPosition() const
    {
        return ship.getPosition();
    }

    float getRadius() const
    {
        return (getBoundaries().size.x / 2);
    }

    void shoot()
    {
        if (!canShoot()) return;
        float angle = ship.getRotation().asRadians();
        sf::Vector2f dir{ std::cos(angle), std::sin(angle) };
        sf::Vector2f spawn = ship.getPosition() + dir * float(ship.getGlobalBounds().size.x *0.75);
        sf::Vector2f vel = dir * projectileSpeed + velocity * velScaler;
        shotTimer = shotCooldown;
        projectiles.push_back(new Projectile(spawn, vel));
    }

    void draw(sf::RenderWindow& window) const 
    {
        window.draw(ship);
        for (const auto& p : projectiles) 
        {
            p->draw(window);
        }
    }

    bool getShieldStatus() const
    {
        return shieldActive;
    }
};