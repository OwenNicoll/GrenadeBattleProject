#include "Platform.h"
#include "AssetManager.h"

Platform::Platform(sf::Vector2f startingPos)
	: SpriteObject()
	
	
{
	solid = true;
	sprite.setTexture(AssetManager::RequestTexture("Assets/tile.png"));
	sprite.setScale(5, 5);
	collisionType = CollisionType::AABB;
	collisionScale = sf::Vector2f(1.0f, 1.0f);
	collisionOffset = sf::Vector2f(0.0f, 0.0f);
	SetPosition(startingPos);
	tag = "Platform";
}


