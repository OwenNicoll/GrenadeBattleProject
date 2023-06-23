#include "VectorHelper.h"

float VectorHelper::SquareMagnitude(sf::Vector2f vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

float VectorHelper::Magnitude(sf::Vector2f vec)
{
	return sqrt(SquareMagnitude(vec));
}

float VectorHelper::DotProduct(sf::Vector2f vec1, sf::Vector2f vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

float VectorHelper::CrossProduct(sf::Vector2f vec1, sf::Vector2f vec2)
{
	return vec1.x * vec2.y - vec1.y * vec2.x;
}

sf::Vector2f VectorHelper::GetNormal(sf::Vector2f line)
{
	return sf::Vector2f(-line.y, line.x);
}


// Practical Task - Reflection
sf::Vector2f VectorHelper::Reflection(sf::Vector2f incomingVec, sf::Vector2f normal)
{
	float dotProduct = DotProduct(incomingVec, normal);
	sf::Vector2f reflection = incomingVec - 2.0f * normal * dotProduct;
	return reflection;
}

sf::Vector2f VectorHelper::Normalise(sf::Vector2f vec)
{
	float mag = Magnitude(vec);

	vec.x = vec.x / mag;
	vec.y = vec.y / mag;


	return vec;
}