#include <SFML/Graphics.hpp>
#include "Player.h"
#include "RoomManager.h"
#include "GameManager.h"

// Finn Gareth Evans
// 24825947

int main()
{
    // Create the main window
    sf::RenderWindow& window = WindowManager::getInstance().getWindow();
    
    GameManager game;

    sf::Clock clock;
    // Start the game loop
    // And keep it running until the window is closed
    while (window.isOpen())
    {
        //Process events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        //get elpased time
        float dt = clock.restart().asSeconds();


        //clear screen and draw 
        window.clear();     
        game.update(dt);
        game.draw(window);
        WindowManager::getInstance().drawUI();
        window.display();   
    }

    return EXIT_SUCCESS;
}