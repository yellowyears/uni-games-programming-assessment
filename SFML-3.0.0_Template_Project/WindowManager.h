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

    WindowManager() : score(0), level(0), gameState(PLAYING), scoreText(font), levelText(font), gameOverText(font)
    {
        int width = (sf::VideoMode::getDesktopMode()).size.x/ 2;
        int height = width * 0.75;

        window = std::make_unique<sf::RenderWindow>(sf::VideoMode(sf::Vector2u(width, height)), "Games Programming Assessment");
        window->setVerticalSyncEnabled(true);
        window->setKeyRepeatEnabled(false);
        textSize = window->getSize().x * 0.04;

        if (!font.openFromFile("assets/font.ttf"))
        {
            std::cout << "Cannot load font!\n";
        }
        hudBar = sf::RectangleShape(sf::Vector2f(window->getSize().x, textSize * 1.2));
        hudBar.setFillColor(sf::Color(50, 50, 50));

        updateScore(score);
        updateLevel(level);
        setGameOverText();
    }

    void setGameOverText()
    {
        gameOverText = sf::Text(font, "GAME OVER", textSize);
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
        gameOverText.setOrigin({ gameOverText.getLocalBounds().size.x / 2,gameOverText.getLocalBounds().size.y / 2 });
    }

public:
    void drawUI() //draw all UI components on screen
    {
        window->draw(hudBar);
        window->draw(scoreText);
        window->draw(levelText);
        if (gameState == GAMEOVER) { setGameOverText();window->draw(gameOverText); }
    }

    void updateScore(int value) //Set score text to the current score
    {
        score = value;
        std::stringstream scoreStream;
        scoreStream << "Score: " << score;
        scoreText = sf::Text(font, scoreStream.str(), textSize);
        scoreText.setOrigin(sf::Vector2f(scoreText.getGlobalBounds().size.x, 0));
        scoreText.setPosition(sf::Vector2f(window->getSize().x - textSize / 2, 0));
    }

    void updateLevel(int value) //Set level text to the current level
    {
        level = value;
        std::stringstream levelStream;
        levelStream << "Level: " << level;
        levelText = sf::Text(font, levelStream.str(), textSize);
        levelText.setPosition(sf::Vector2f(textSize / 2, 0));
    }

    static WindowManager& getInstance() // (create and) return Singleton instance
    {
        static WindowManager gameWindow;
        return gameWindow;
    }

    sf::RenderWindow& getWindow() const //return a ref to the render window
    {
        return *window;
    }

    const sf::Vector2u& getSize() const //gets size of window
    {
        return window->getSize();
    }

    void setGameOver()  //set state of UI to gameover
    {
        gameState = GAMEOVER;
    }
};
