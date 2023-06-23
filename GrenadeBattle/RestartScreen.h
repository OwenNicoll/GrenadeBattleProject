#pragma once
#include "Screen.h"
#include "MenuPanel.h"


class RestartScreen :
    public Screen
{
public:
    RestartScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;


private:

    MenuPanel* panel;
    sf::Text titleText;
    sf::Text restartText;
    sf::Font font;
};

