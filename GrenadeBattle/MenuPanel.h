#pragma once
#include "SpriteObject.h"
class MenuPanel :
    public SpriteObject
{

public:
    MenuPanel();

    void Update(sf::Time frameTime) override;

    float easingFunction(float t, float b, float c, float d);


private:
    sf::Clock clock;
    float startPosX;
    float startPosY;
    float endPosX;
    float endPosY;
    float duration;

};

