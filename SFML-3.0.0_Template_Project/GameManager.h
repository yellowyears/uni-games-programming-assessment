#pragma once
#include "Player.h"
#include "BaseEnemy.h"
#include "Projectile.h"
#include "RoomManager.h"
#include "WindowManager.h"

class GameManager
{
	Player* player;
	RoomManager* roomManager;
	std::vector<BaseEnemy*> baseEnemies;
	std::vector<SmartEnemy*> smartEnemies;
	std::vector<Projectile*> projectiles;
	sf::Vector2u windowSize;
	int level, score;
	enum STATE { PLAYING, GAMEOVER };
	STATE gameState;

public:
	GameManager() : windowSize(WindowManager::getInstance().getSize()), level(1), score(0), gameState(PLAYING)
	{
		player = new Player(projectiles, sf::Vector2f(windowSize.x / 2, windowSize.y / 2));
		roomManager = new RoomManager(sf::FloatRect({ 0,0 }, sf::Vector2f(windowSize.x, windowSize.y)), baseEnemies, smartEnemies, level);
		WindowManager::getInstance().updateLevel(level);
	}

	/*********************************Task A - iii * ************************************************************
	Add a destructor to the GameManager class to properly release dynamically allocated memory and clean up resources when the objects are destroyed.
	************************************************************************************************************************/
	
	void draw(sf::RenderWindow& window) const
	{
		roomManager->draw(window);
		player->draw(window);
	}

	void update(float dt)
	{
		if (gameState == PLAYING)
		{
			roomManager->update(dt, player->getPosition());
			player->update(dt);

			resolvePlayerCollisionWithEnemies(*player, baseEnemies, smartEnemies);
			resolveProjectilesCollisionWithBaseEnemies(projectiles, baseEnemies);
			resolveProjectilesCollisionWithSmartEnemies(projectiles, smartEnemies);
		}
	}

private:
	//collision resolution methods
	void resolvePlayerCollisionWithEnemies(Player& player, std::vector<BaseEnemy*>& baseEnemies, std::vector<SmartEnemy*>& smartEnemies)
	{
		for (size_t i = 0; i < baseEnemies.size(); ++i)
		{
			if (checkCollisionBetweenBaseEnemyAndPlayer(*baseEnemies[i], player))
			{
				if (!player.getShieldStatus())
				{
					gameState = GAMEOVER;
					WindowManager::getInstance().setGameOver();
				}
				else
				{
					baseEnemies.erase(baseEnemies.begin() + i);
				}
			}
		}

		for (size_t i = 0; i < smartEnemies.size(); ++i)
		{
			if (checkCollisionBetweenSmartEnemyAndPlayer(*smartEnemies[i], player))
			{
				if (!player.getShieldStatus())
				{
					gameState = GAMEOVER;
					WindowManager::getInstance().setGameOver();
				}
				else
				{
					smartEnemies.erase(smartEnemies.begin() + i);
				}
			}
		}
	}

	void resolveProjectilesCollisionWithBaseEnemies(std::vector<Projectile*>& projectiles, std::vector<BaseEnemy*>& baseEnemies)
	{
		for (size_t i = 0; i < baseEnemies.size(); ++i)
		{
			for (size_t j = 0; j < projectiles.size(); ++j)
			{
				if (checkCollisionBetweenProjectileAndBaseEnemy(*baseEnemies[i], *projectiles[j]))
				{
					score++;
					WindowManager::getInstance().updateScore(score);
					projectiles.erase(projectiles.begin() + j);
					baseEnemies.erase(baseEnemies.begin() + i);
					break;
				}
			}
		}
	}

	void resolveProjectilesCollisionWithSmartEnemies(std::vector<Projectile*>& projectiles, std::vector<SmartEnemy*>& smartEnemies)
	{
		for (size_t i = 0; i < smartEnemies.size(); ++i)
		{
			for (size_t j = 0; j < projectiles.size(); ++j)
			{
				if (checkCollisionBetweenProjectileAndSmartEnemy(*smartEnemies[i], *projectiles[j]))
				{
					score++;
					WindowManager::getInstance().updateScore(score);
					projectiles.erase(projectiles.begin() + j);
					if (smartEnemies[i]->isShielded()) smartEnemies[i]->removeShield();
					else smartEnemies.erase(smartEnemies.begin() + i);
					break;
				}
			}
		}
	}

	/************************************************Task A-vi***************************************************************
	Refactor the similar collision detection methods to use a single function template instead, name it CheckCollisionBetweenTwoObjects.
	************************************************************************************************************************/

	//collision detection methods
	bool checkCollisionBetweenBaseEnemyAndPlayer(BaseEnemy& enemy, Player& player) const
	{
		sf::Vector2f pos1 = enemy.getPosition();
		sf::Vector2f pos2 = player.getPosition();

		float distance = std::sqrt(std::pow(pos2.x - pos1.x, 2) + std::pow(pos2.y - pos1.y, 2));
		float combinedRadii = enemy.getRadius() + player.getRadius();
		return distance <= combinedRadii;
	}

	bool checkCollisionBetweenSmartEnemyAndPlayer(SmartEnemy& enemy, Player& player) const
	{
		sf::Vector2f pos1 = enemy.getPosition();
		sf::Vector2f pos2 = player.getPosition();

		float distance = std::sqrt(std::pow(pos2.x - pos1.x, 2) + std::pow(pos2.y - pos1.y, 2));
		float combinedRadii = enemy.getRadius() + player.getRadius();
		return distance <= combinedRadii;
	}

	bool checkCollisionBetweenProjectileAndBaseEnemy(BaseEnemy& enemy, Projectile& projectile) const
	{
		sf::Vector2f pos1 = enemy.getPosition();
		sf::Vector2f pos2 = projectile.getPosition();

		float distance = std::sqrt(std::pow(pos2.x - pos1.x, 2) + std::pow(pos2.y - pos1.y, 2));
		float combinedRadii = enemy.getRadius() + projectile.getRadius();
		return distance <= combinedRadii;
	}

	bool checkCollisionBetweenProjectileAndSmartEnemy(SmartEnemy& enemy, Projectile& projectile) const
	{
		sf::Vector2f pos1 = enemy.getPosition();
		sf::Vector2f pos2 = projectile.getPosition();

		float distance = std::sqrt(std::pow(pos2.x - pos1.x, 2) + std::pow(pos2.y - pos1.y, 2));
		float combinedRadii = enemy.getRadius() + projectile.getRadius();
		return distance <= combinedRadii;
	}

};
