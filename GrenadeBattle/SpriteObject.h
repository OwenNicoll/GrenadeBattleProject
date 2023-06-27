#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class CollisionType
{
	CIRCLE,
	AABB
};

class SpriteObject
{
public:

	SpriteObject();

	virtual void Update(sf::Time framTime);
	virtual void Draw(sf::RenderTarget& target);

	void SetPosition(float posX, float posY);
	void SetPosition(sf::Vector2f newPosition);
	sf::Vector2f GetPosition();

	bool CheckCollision(SpriteObject otherObject);
	sf::Vector2f GetCollisionDepth(SpriteObject other);
	virtual void HandleCollision(SpriteObject& _other);
	bool GetSolid();

	std::string GetTag();
	void SetTag(std::string newTag);

	void SetColliding(bool colliding);

	bool GetAlive();
	void SetAlive(bool newAlive);

	sf::Sprite GetSprite();

	sf::Vector2f GetSide();
	sf::Vector2f GetTop();

	sf::Vector2f GetBoundingRectSize();
private:

	sf::Vector2f GetCollisionCentre();
	float GetBoundingCircleRadius();
	
	sf::FloatRect GetAABB();
	CollisionType GetCollisionType();

protected:

	sf::Sprite sprite;

	// Collision settings
	sf::Vector2f collisionOffset;
	sf::Vector2f collisionScale;

	CollisionType collisionType;
	bool solid;
	bool alive;
	std::string tag;

private:
	sf::Vector2f position;
	bool colliding;
	


};

