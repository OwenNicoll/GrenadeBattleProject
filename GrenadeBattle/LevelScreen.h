#pragma once
#include "Screen.h"
 #include "Player.h"
#include "MenuPanel.h"
#include <SFML/Graphics.hpp>

class Game;
class Platform;

class LevelScreen :
    public Screen
{

public:
    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void LoadNextLevel();
    void LoadLevel();
    bool LoadLevel(std::string fileName);
   


private:

     Player player;
     Player player2;

  


     std::vector<Platform*> platforms;
     
     sf::Text player1Lives;
     sf::Text player2Lives;
     sf::Font font;

    sf::View camera;

    int currentLevel;


};
