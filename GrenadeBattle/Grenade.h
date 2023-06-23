#pragma once
#include "SpriteObject.h"

class Grenade :
    public SpriteObject
{

public:


    Grenade(sf::Vector2f position, sf::Vector2f velocity);

    void Test();

    void Update(sf::Time frameTime) override;

    void HandleCollision(SpriteObject& _other) override;

    bool reflect;

private:

 
    sf::Vector2f velocity;
    sf::Vector2f acceleration;;
    sf::Vector2f reflectionVector;
    int bounceCounter;
    bool canBounce;
   

};

