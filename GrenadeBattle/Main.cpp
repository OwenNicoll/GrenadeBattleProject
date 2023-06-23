
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include "AssetManager.h"
#include <SFML/Audio.hpp>
int main()
{

    

    // Initialise the random number generator
    srand(time(NULL));

    // Create the game
    Game gameInstance; // default constructor


    // This will not end until the game is over
    gameInstance.RunGameLoop();




    // If we get here, the loop exited, so the game is over

    // Clean up assets
    AssetManager::DestroyAllAssets();

    // End the program by returning
    return 0;














   /* sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;*/
}