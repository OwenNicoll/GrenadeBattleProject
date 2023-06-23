#include "MenuPanel.h"
#include "AssetManager.h"

MenuPanel::MenuPanel()
    :startPosX()
    ,startPosY()
    ,endPosX()
    ,endPosY()
    ,duration()
{

    sprite.setTexture(AssetManager::RequestTexture("Assets/MenuPanel.png"));
    sprite.setScale(1, 1);

    duration = 1.0f;
    startPosX = 700;
    startPosY = 1100;

    endPosX = 700;
    endPosY = 300;

    SetPosition(startPosX, startPosY);

    clock.restart();
}

void MenuPanel::Update(sf::Time frameTime)
{

    float elapsedTime = clock.getElapsedTime().asSeconds();

    if (elapsedTime <= duration)
    {
        float newPosX = easingFunction(elapsedTime, startPosX, endPosX - startPosX, duration);
        float newPosY = easingFunction(elapsedTime, startPosY, endPosY - startPosY, duration);

        SetPosition(newPosX, newPosY);
    }
    
    SpriteObject::Update(frameTime);
}

// Practical Task - Easing Function
float MenuPanel::easingFunction(float t, float b, float c, float d)
{
    t /= d;
    return (c * (t * t)) / (d * d) + b;
}
