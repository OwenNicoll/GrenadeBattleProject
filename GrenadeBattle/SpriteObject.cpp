#include "SpriteObject.h"
#include "VectorHelper.h"
#include <algorithm>
#include <iostream>

SpriteObject::SpriteObject()
	: sprite()
	, collisionOffset(0, 0)
	, collisionScale(1, 1)
	, collisionType(CollisionType::AABB)
	, position(0, 0)
	, colliding(false)
	, solid(false)
	, alive(true)
{
}

void SpriteObject::Update(sf::Time frameTime)
{
	SetColliding(false);
}

void SpriteObject::Draw(sf::RenderTarget& target)
{
	if (!alive)
		return; 

	target.draw(sprite);

	bool drawCollision = false;

	if (drawCollision)
	{
		switch (collisionType)
		{
		case CollisionType::CIRCLE:
		{
			sf::CircleShape circleCollision;
			float radius = GetBoundingCircleRadius();
			circleCollision.setPosition(GetCollisionCentre());
			circleCollision.setRadius(GetBoundingCircleRadius());
			circleCollision.setOrigin(radius, radius);
			sf::Color collisionColour = sf::Color::Green;
			if (colliding)
				collisionColour = sf::Color::Red;
			collisionColour.a = 100;
			circleCollision.setFillColor(collisionColour);
			target.draw(circleCollision);
			break;
		}
		case CollisionType::AABB:
		{
			sf::RectangleShape rectCollision;
			rectCollision.setPosition(GetCollisionCentre() - GetBoundingRectSize() / 2.0f);
			rectCollision.setSize(GetBoundingRectSize());
			sf::Color collisionColour = sf::Color::Green;
			if (colliding)
				collisionColour = sf::Color::Red;
			collisionColour.a = 100;
			rectCollision.setFillColor(collisionColour);
			target.draw(rectCollision);
			break;
		}
		break;
		default:
			break;
		}
	}
}


void SpriteObject::SetPosition(float posX, float posY)
{
	SetPosition(sf::Vector2f(posX, posY));
}

void SpriteObject::SetPosition(sf::Vector2f _position)
{
	position = _position;
	sprite.setPosition(position);
}

sf::Vector2f SpriteObject::GetPosition()
{
	return position;
}

sf::Vector2f SpriteObject::GetCollisionCentre()
{
	float width = sprite.getGlobalBounds().height;
	float height = sprite.getGlobalBounds().width;
	sf::Vector2f centre = position;
	centre.x += width / 2.0f;
	centre.y += height / 2.0f;
	centre += collisionOffset;
	return centre;
}

float SpriteObject::GetBoundingCircleRadius()
{
	float width = sprite.getGlobalBounds().height;
	width *= collisionScale.x;
	float height = sprite.getGlobalBounds().width;
	height *= collisionScale.y;
	float radius = width / 2.0f;
	if (height > width)
		radius = height / 2.0f;
	return radius;
}

sf::Vector2f SpriteObject::GetBoundingRectSize()
{
	float width = sprite.getGlobalBounds().height;
	width *= collisionScale.x;
	float height = sprite.getGlobalBounds().width;
	height *= collisionScale.y;
	return sf::Vector2f(width, height);
}

sf::FloatRect SpriteObject::GetAABB()
{
	sf::Vector2f topLeft = GetCollisionCentre() - GetBoundingRectSize() / 2.0f;
	sf::FloatRect rect = sf::FloatRect(topLeft, GetBoundingRectSize());
	return sf::FloatRect(rect);
}

CollisionType SpriteObject::GetCollisionType()
{
	return collisionType;
}

bool SpriteObject::CheckCollision(SpriteObject _otherObject)
{
	if (!alive || !_otherObject.alive)
		return false; // Exit early if one of hte two objects is dead

	

	switch (collisionType)
	{
	case CollisionType::CIRCLE:
	{
		if (_otherObject.GetCollisionType() == CollisionType::CIRCLE)
		{
			sf::Vector2f otherCentre = _otherObject.GetCollisionCentre();
			float otherRadius = _otherObject.GetBoundingCircleRadius();

			sf::Vector2f distanceVector = otherCentre - GetCollisionCentre();

			float distanceSquare = VectorHelper::SquareMagnitude(distanceVector);

			float minDistance = otherRadius + GetBoundingCircleRadius();
			float minDistanceSquare = minDistance * minDistance;

			return distanceSquare <= minDistanceSquare;
		}
		else
		{
			// Clamp our coordinates to other's box size
			sf::Vector2f clampedCentre = GetCollisionCentre();
			sf::FloatRect otherRect = _otherObject.GetAABB();
			clampedCentre.x = std::fmaxf(otherRect.left, std::fminf(clampedCentre.x,
				otherRect.left + otherRect.width));
			clampedCentre.y = std::fmaxf(otherRect.top, std::fminf(clampedCentre.y,
				otherRect.top + otherRect.height));

			sf::Vector2f distanceVec = clampedCentre - GetCollisionCentre();
			float distance = VectorHelper::Magnitude(distanceVec);

			return distance <= GetBoundingCircleRadius();
		}
		break;
	}



	//Practical Task - Collision Geometry

	case CollisionType::AABB:
	{
		if (_otherObject.GetCollisionType() == CollisionType::AABB)
		{
			return GetAABB().intersects(_otherObject.GetAABB());
		}
		else
		{
			// Clamp our coordinates to other's box size
			sf::Vector2f clampedCentre = _otherObject.GetCollisionCentre();
			sf::FloatRect otherRect = GetAABB();
			clampedCentre.x = std::fmaxf(otherRect.left, std::fminf(clampedCentre.x,
				otherRect.left + otherRect.width));
			clampedCentre.y = std::fmaxf(otherRect.top, std::fminf(clampedCentre.y,
				otherRect.top + otherRect.height));

			sf::Vector2f distanceVec = clampedCentre - _otherObject.GetCollisionCentre();
			float distance = VectorHelper::Magnitude(distanceVec);

			return distance <= _otherObject.GetBoundingCircleRadius();
		}
		break;
	}
	break;
	default:

		return false;
		break;
	}
}

sf::Vector2f SpriteObject::GetCollisionDepth(SpriteObject _otherObject)
{
	sf::FloatRect thisAABB = GetAABB();
	sf::FloatRect otherAABB = _otherObject.GetAABB();

	sf::Vector2f thisCentre = GetCollisionCentre();
	sf::Vector2f otherCentre = _otherObject.GetCollisionCentre();

	sf::Vector2f minDistance;
	minDistance.x = thisAABB.width * 0.5f + otherAABB.width * 0.5f;
	minDistance.y = thisAABB.height * 0.5f + otherAABB.height * 0.5f;

	sf::Vector2f actualDistance = otherCentre - thisCentre;

	// correct minDistance to be the same sign as actual distance
	if (actualDistance.x < 0)
		minDistance.x = -minDistance.x;
	if (actualDistance.y < 0)
		minDistance.y = -minDistance.y;

	sf::Vector2f depth = actualDistance - minDistance;



	return depth;
}

void SpriteObject::HandleCollision(SpriteObject& _other)
{
	SetColliding(true);
}

bool SpriteObject::GetSolid()
{
	return solid;
}

std::string SpriteObject::GetTag()
{
	return tag;
}

void SpriteObject::SetTag(std::string newTag)
{
	tag = newTag;
}

sf::Sprite SpriteObject::GetSprite()
{
	return sprite;
}

void SpriteObject::SetColliding(bool _colliding)
{
	colliding = _colliding;
}

bool SpriteObject::GetAlive()
{
	return alive;
}

void SpriteObject::SetAlive(bool _newAlive)
{
	alive = _newAlive;
}
