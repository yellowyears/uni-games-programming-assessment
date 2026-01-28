/*----------------------------------------------------Assessment Task-------------------------------------------------------------
	Refactor the code so that WindowManager.h contains the class definition and WindowManager.cpp contains the implementation.
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

class WindowManager
{
private:
	float textSize;
	int score, level;
	enum STATE { PLAYING, GAMEOVER };
	STATE gameState;

	std::unique_ptr<sf::RenderWindow> window;

	sf::Font font;
	sf::Text scoreText, levelText, gameOverText;
	sf::RectangleShape hudBar;
	sf::Texture upgradeTextures[];

	WindowManager();

	void setGameOverText();

public:
	void drawUI();

	void updateScore(int value); //Set score text to the current score

	void updateLevel(int value); //Set level text to the current level

	static WindowManager& getInstance(); // (create and) return Singleton instance

	sf::RenderWindow& getWindow() const; //return a ref to the render window

	const sf::Vector2u& getSize() const; //gets size of window

	void setGameOver();  //set state of UI to gameover
};
