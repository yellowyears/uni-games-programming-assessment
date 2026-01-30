#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include <vector>
#include <random>
#include <iostream>
#include "Component.h"

class Player; // Forward declaration of player prevents circular dependency

class MovementComponent : public Component
{
    float maxSpeed = 350.f;
    float thrustPower = 250.f;

public:
    MovementComponent() : Component("Movement") {}

    void Update(float dt) override
    {
        ///************************************* Movement *********************************/
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) parent.ship.rotate(sf::degrees(-maxSpeed * dt));
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) parent.ship.rotate(sf::degrees(maxSpeed * dt));
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        //{
        //    sf::Vector2f forward{ std::cos(float(parent.ship.getRotation().asRadians())), std::sin(float(parent.ship.getRotation().asRadians())) };
        //    parent.velocity += forward * thrustPower * dt;
        //}

        //float sp = parent.velocity.length();
        //if (sp > maxSpeed) parent.velocity = parent.velocity.normalized() * maxSpeed;
        //parent.velocity *= (1.0f - std::min(dt * 2.5f, 1.0f)); // simple damping
        //parent.ship.move(parent.velocity * dt);
    }
};

class ShootingComponent : public Component
{
    float shotCooldown = 0.22f;
    float shotTimer = 0.f;
    float projectileSpeed = 520;
    float velScaler = 0.2f;

public:
    ShootingComponent() : Component("Shooting") {}

    void Update(float dt) override
    {
        /************************************* Shooting *********************************/
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) shoot(parent);
        //shotTimer -= dt;
        //for (const auto& p : parent.projectiles)
        //{
        //    p->update(dt);
        //}

        //for (auto it = parent.projectiles.begin(); it != parent.projectiles.end(); )
        //{
        //    if ((*it)->shouldDestroy())
        //    {
        //        it = parent.projectiles.erase(it);
        //    }
        //    else
        //    {
        //        ++it;
        //    }
        //}
    }

    void shoot(Player& parent)
    {
        //if (!canShoot()) return;
        //float angle = parent.ship.getRotation().asRadians();
        //sf::Vector2f dir{ std::cos(angle), std::sin(angle) };
        //sf::Vector2f spawn = parent.getPosition() + dir * float(parent.ship.getGlobalBounds().size.x * 0.75);
        //sf::Vector2f vel = dir * projectileSpeed + parent.velocity * velScaler;
        //shotTimer = shotCooldown;
        //parent.projectiles.push_back(new Projectile(spawn, vel));
    }

    bool canShoot() const
    {
        return shotTimer <= 0.f;
    }
};

class ShieldingComponent : public Component
{
    bool shieldActive = false;
    sf::Clock shieldTimer;
    sf::Clock shieldCooldown;

public:
    ShieldingComponent() : Component("Shielding") {}

	//void Update(Player& parent, float dt) override
	//{
		//std::cout << "Updating physics" << std::endl;

  //      /************************************* Shielding *********************************/
  //      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && !shieldActive && shieldCooldown.getElapsedTime().asSeconds() > 2)
  //      {
  //          shieldActive = true;
  //          parent.ship.setOutlineThickness(4);
  //          shieldTimer.restart();
  //      }

  //      if (shieldActive && shieldTimer.getElapsedTime().asSeconds() > 3)
  //      {
  //          shieldActive = false;
  //          parent.ship.setOutlineThickness(0);
  //          shieldCooldown.restart();
  //      }
	//}

    void Init()
    {
        shieldCooldown.start();
    }

    bool getShieldStatus() const
    {
        return shieldActive;
    }
};