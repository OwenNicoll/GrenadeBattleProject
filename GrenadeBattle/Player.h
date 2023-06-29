#pragma once
#include "SpriteObject.h"
#include "Pip.h"
#include "Grenade.h"



class Player :
    public SpriteObject
{

public:

    Player();

    void Update(sf::Time frameTime) override;

    void HandleCollision(SpriteObject& _other) override;

    void SetEnemy(Player* newEnemy);
    Player* GetEnemy();

    void SetController(unsigned int newIndex);

    std::vector<Grenade*> GetGrenadeVector();

    sf::Vector2f GetStartingPos();
    void SetStartingPos(sf::Vector2f newStartingPos);

    

    int GetLives();

    float GetRightStickX();
    float GetRightStickY();


    float GetLeftStickX();
    
    void ClearGrenadeVector();

    std::vector<Pip> GetPipVector();


    bool GetWin();
    void SetWin();

    bool GetCanJump();

private:
    
    std::vector<Pip> pipVector;
    

    sf::Clock clock;

    sf::Vector2f GetPipPosition(float t);
    std::vector<Grenade*> grenadeVector;
    void UpdateAcceleration();
   
    sf::Vector2f grenadeVelocity;
    sf::Vector2f grenadeAcceleration;
    Player* enemy;
    unsigned int joystickIndex;

    std::string spritePath;


    sf::Vector2f twoFramesOldPos;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Clock deltaClock;
    bool canJump;
    sf::Vector2f initialPosition;
    sf::Vector2f initialVelocity;
    sf::Vector2f gravity;
    sf::Vector2f startingPos;


    bool win;
    int lives;
};

