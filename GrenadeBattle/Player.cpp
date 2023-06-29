#include "Player.h"
#include "AssetManager.h"
#include "Grenade.h"
#include <SFML/Audio.hpp>
#include <iostream>


enum class PhysicsType {
	
	BACKWARD_EULER,
	SYMPLECTIC_EULER,
	POSITION_VERLET,
	VELOCITY_VERLET
};




Player::Player()
	: SpriteObject()
	, twoFramesOldPos(100, 300)
	, velocity(0, 0)
	, acceleration(0, 0)
	, canJump(false)
	, deltaClock()
	, initialPosition(GetPosition())
	, initialVelocity(500, -0)
	, gravity(0, 2000)
	, grenadeAcceleration(0, 1000)
	, grenadeVelocity(500, -500)
	,lives(3)
	,joystickIndex(0)
	,clock()
	,spritePath()
	,win(false)

{
	if (joystickIndex == 0)
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/player_1_stand.png"));
	}
	else if (joystickIndex == 1)
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/player_2_stand.png"));
	}
	
	sprite.setPosition(GetPosition());
	sprite.setScale(3, 3);

	collisionScale = sf::Vector2f(0.5f, 0.70f);
	collisionOffset = sf::Vector2f(0, 0);
	collisionType = CollisionType::AABB;

	
}

void Player::Update(sf::Time frameTime)
{
	// Return if player is not alive
	if (!alive)
		return;

	// Drag
	const float DRAG_MULT = 10.0f;
	const PhysicsType physics = PhysicsType::BACKWARD_EULER;


	float elapsedTime = clock.getElapsedTime().asSeconds();


	// Animation properties
	const int FRAME_COUNT = 4;          // Number of animation frames
	const float ANIMATION_SPEED = 0.2f; // Animation speed (lower values result in slower animation)

	// Calculate the current frame index based on elapsed time and animation speed
	int frameIndex = static_cast<int>(elapsedTime / ANIMATION_SPEED) % FRAME_COUNT;

	spritePath = "Assets/player_1_walk_" + std::to_string(frameIndex) + ".png";

	// Set the sprite based on the current frame index
	
	
	
	


	sf::SoundBuffer& boomSoundBuffer = AssetManager::RequestSoundBuffer("Assets/shoot.wav");
	sf::Sound boomSound;
	boomSound.setBuffer(boomSoundBuffer);

	boomSound.play();

	// PRACTICAL TASK - PHYSICS ALTERNATIVES

	switch (physics)
	{
	

	case PhysicsType::BACKWARD_EULER:
		{


			// Backward Euler, velocity is calculated first
			
			// Update acceleration
			UpdateAcceleration();

			velocity = velocity + acceleration * frameTime.asSeconds();

			// drag
			velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();

			SetPosition(GetPosition() + velocity * frameTime.asSeconds());

		}
		break;

	case PhysicsType::SYMPLECTIC_EULER:
		{
			// SEMI-IMPLICIT / SYMPLECTIC_EULER

			velocity = velocity + acceleration * frameTime.asSeconds();

			// drag
			velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();

			SetPosition( GetPosition() + velocity * frameTime.asSeconds());

			// Update acceleration
			UpdateAcceleration();
		}
		break;

	break;

	case PhysicsType::VELOCITY_VERLET:
	{
		// VELOCITY VERLET / LEAP FROG

		// Get half frame velocity using
		// previous frame's acceleration
		sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;

		// Get new frame's position using half frame velocity
		SetPosition( GetPosition() + halfFrameVelocity * frameTime.asSeconds());

		// Update our current acceleration
		UpdateAcceleration();

		// Get new frame's velocity using half frame velocity and
		// updated acceleration
		velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;

		// drag
		velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();
	}
	break;

	default:
		break;
	}

	
//	sf::Vector2f offset(200, -200);


	if (sf::Joystick::isButtonPressed(joystickIndex, sf::Joystick::V))
	{
		if (grenadeVector.size() < 1)
		{
			Grenade* grenade = new Grenade(GetPosition() + sf::Vector2f(0, -50), initialVelocity);
			
			grenadeVector.push_back(grenade);
			grenade->SetTag(GetTag() + " grenade");
			elapsedTime = clock.restart().asSeconds();

			
		}
		

	}

	if (lives <= 0)
	{
		alive = false;
	}

	

	bool isRightStickHeldy = false;

	float rightSticky = GetRightStickY();

	if (rightSticky > 10) 
	{
		if (!isRightStickHeldy)
		{
			isRightStickHeldy = true;
		
		}

		if (initialVelocity.y <= 700)
		{
			initialVelocity.y += 10;
		}
	}
	else if (rightSticky < -10) 
	{
		if (!isRightStickHeldy)
		{
			isRightStickHeldy = true;
			
		}

		if (initialVelocity.y >= -700)
		{
			initialVelocity.y -= 10;
		}
	}
	else
	{
		isRightStickHeldy = false; 
	}




	bool isRightStickHeldx = false;

	float rightStickX = GetRightStickX();

	if (rightStickX > 10) 
	{
		if (!isRightStickHeldx)
		{
			isRightStickHeldx = true;
			
		}

		if (initialVelocity.x <= 700)
		{
			initialVelocity.x += 10; 
		}
	}
	else if (rightStickX < -10) 
	{
		if (!isRightStickHeldx)
		{
			isRightStickHeldx = true;
			
		}

		if (initialVelocity.x >= -700)
		{
			initialVelocity.x -= 10; 
		}
	}
	else
	{
		isRightStickHeldx = false; 
	}


	// Erase grenades if they are not alive
	for (int i = 0; i < grenadeVector.size(); i++)
	{
		if (grenadeVector[i]->GetAlive() == false)
		{
			ClearGrenadeVector();
		}
	}


	for (int i = 0; i < 5; i++)
	{
		Pip newPip;
		pipVector.push_back(newPip);
	}
	

	//Practical Task - Gravity Prediction
	pipVector[0].SetPosition(GetPipPosition(0));
	pipVector[1].SetPosition(GetPipPosition(0.1f));
	pipVector[2].SetPosition(GetPipPosition(0.2f));
	pipVector[3].SetPosition(GetPipPosition(0.3f));
	pipVector[4].SetPosition(GetPipPosition(0.4f));


	initialPosition = GetPosition() + sf::Vector2f(25, 50);

	for (int i = 0; i < 5; i++)
	{
		pipVector[i].Update(frameTime);
	}


	

	if (elapsedTime >= 1.5)
	{
		ClearGrenadeVector();
	}


	if (sf::Joystick::isButtonPressed(joystickIndex, sf::Joystick::X))
	{

		if (canJump)
		{
			velocity.y = -2000;
			canJump = false;
		}

	}

	SpriteObject::Update(frameTime);

}

void Player::HandleCollision(SpriteObject& _other)
{
	if (_other.GetSolid())
	{
		sf::Vector2f depth = GetCollisionDepth(_other);
		sf::Vector2f newPos = GetPosition();

		if (abs(depth.x) < abs(depth.y))
		{
			// Move on x axis
			newPos.x += depth.x;
			velocity.x = 0;
			acceleration.x = 0;
		}
		else
		{
			// If we were falling and we collided in the y direction and we're on the top side of the platform...
			if (velocity.y > 0 && depth.y < 0)
			{
				canJump = true;

				// Move on y axis
			
				velocity.y = 0;
				acceleration.y = 0;
			}
		
			newPos.y += depth.y;
			
		}

		SetPosition(newPos);
	}

	if (_other.GetTag() == "Platform")
	{

	}

	// Check if we collided with enemy grenade

	if (_other.GetTag() == enemy->GetTag() + " grenade")
	{
		// Decrease lives
		lives--;

		// Set position
		SetPosition(startingPos);

		// Set enemy position
		enemy->SetPosition(enemy->startingPos);

		// Clear Grenades
		ClearGrenadeVector();

		// Clear enemy grenades
		enemy->ClearGrenadeVector();
	}

	if (_other.GetTag() == "Platform")
	{
		//SetPosition(500, 500);
	}
	SpriteObject::HandleCollision(_other);
}

void Player::SetEnemy(Player* newEnemy)
{
	enemy = newEnemy;
}

Player* Player::GetEnemy()
{
	return enemy;
}

void Player::SetController(unsigned int newIndex)
{
	joystickIndex = newIndex;
}

std::vector<Grenade*> Player::GetGrenadeVector()
{
	return grenadeVector;
}

sf::Vector2f Player::GetStartingPos()
{
	return startingPos;
}

void Player::SetStartingPos(sf::Vector2f newStartingPos)
{
	startingPos = newStartingPos;
}

bool Player::GetWin()
{
	return win;
}

void Player::SetWin()
{
	win = true;
}

bool Player::GetCanJump()
{
	return canJump;
}



//Practical Task - Gravity Prediction

sf::Vector2f Player::GetPipPosition(float t)
{
	
	sf::Vector2f finalPosition = (initialPosition + sf::Vector2f(0, -50)) + (initialVelocity) * t + (0.5f * grenadeAcceleration * (t * t));
	return finalPosition;

}

void Player::UpdateAcceleration()
{
	const float ACCEL = 5000;
	const float GRAVITY = 5000;
	const float JUMP = 2000;
	

	// Update acceleration
	acceleration.x = 0;
	acceleration.y = GRAVITY;
	

	
	
	if (GetLeftStickX() < -10)
	{
		acceleration.x = -ACCEL;
		sprite.setTexture(AssetManager::RequestTexture(spritePath));
	}
	if (GetLeftStickX() > 10)
	{
		acceleration.x = ACCEL;
		sprite.setTexture(AssetManager::RequestTexture(spritePath));
	}

}



int Player::GetLives()
{
	return lives;
}

float Player::GetRightStickX()
{
	return sf::Joystick::getAxisPosition(joystickIndex, sf::Joystick::Axis::U);
}

float Player::GetRightStickY()
{
	return sf::Joystick::getAxisPosition(joystickIndex, sf::Joystick::Axis::V);
}

float Player::GetLeftStickX()
{
	return sf::Joystick::getAxisPosition(joystickIndex, sf::Joystick::X);
}

void Player::ClearGrenadeVector()
{
	for (int i = 0; i < grenadeVector.size(); i++)
	{
		auto it = std::find(grenadeVector.begin(), grenadeVector.end(), grenadeVector[i]);
		if (it != grenadeVector.end())
		{
			grenadeVector.erase(it);
		}
	}
}

std::vector<Pip> Player::GetPipVector()
{
	return pipVector;
}




