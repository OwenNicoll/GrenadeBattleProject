#include "Grenade.h"
#include "Player.h"
#include "AssetManager.h"
#include <iostream>
#include "VectorHelper.h"


Grenade::Grenade(sf::Vector2f position, sf::Vector2f velocity)
	: velocity(velocity.x, velocity.y)
	, acceleration(0, 1000)
	, bounceCounter(0)
	, canBounce(true)
	
	
{

	sprite.setTexture(AssetManager::RequestTexture("Assets/grenade.png"));
	sprite.setScale(5, 5);
	collisionType = CollisionType::CIRCLE;
	collisionScale = sf::Vector2f(0.33f, 0.33f);
	SetPosition(position);
	velocity = sf::Vector2f(500, -500);
	reflectionVector = sf::Vector2f(-0, 0);
}

void Grenade::Test()
{
}

void Grenade::Update(sf::Time frameTime)
{
	canBounce = true;

	velocity += acceleration * frameTime.asSeconds();

	SetPosition(GetPosition() + velocity * frameTime.asSeconds());
	

	if (bounceCounter >= 5)
	{
		//alive = false;
	}



	//std::cout << "velX: " << velocity.x << std::endl;
    //std::cout << "velY " << velocity.y << std::endl;

			
}

void Grenade::HandleCollision(SpriteObject& _other)
{


	if (_other.GetTag() == "Platform")
	{
		
				
		// Practical Task - Reflection
		 sf::Vector2f depth = GetCollisionDepth(_other);


		 // We hit side of platform
		 if (abs(depth.x) < abs(depth.y))
		 {
			 sf::Vector2f line(_other.GetSide());
			 sf::Vector2f normal = VectorHelper::GetNormal(line);
			 normal = VectorHelper::Normalise(normal);
			 sf::Vector2f reflection = VectorHelper::Reflection(velocity, normal);
			 velocity = reflection;
			 
		 }

		 // We hit the top of platform
		 else if (abs(depth.x) > abs(depth.y))
		 {
			 sf::Vector2f line(_other.GetTop());
			 sf::Vector2f normal = VectorHelper::GetNormal(line);
			 normal = VectorHelper::Normalise(normal);
			 sf::Vector2f reflection = VectorHelper::Reflection(velocity, normal);
			 velocity = reflection;
		 }


		
		
		

		
		if (canBounce)
		{
			bounceCounter++;
			canBounce = false;
		}
		
		if (velocity.x == 0)
		{
			SetPosition(depth.y, GetPosition().x);
		}

		if (velocity.y == 0)
		{
			SetPosition(GetPosition().x, depth.y);
		}
		
	}

	if (_other.GetTag() == "Player")
	{
		//_other.SetAlive(false);
		//SetAlive(false);
		

	}
	SpriteObject::HandleCollision(_other);
}
	

	



