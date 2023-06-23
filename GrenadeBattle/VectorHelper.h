#pragma once
#include <SFML/System.hpp>

namespace VectorHelper {

	float SquareMagnitude(sf::Vector2f vec);
	float Magnitude(sf::Vector2f vec);
	float DotProduct(sf::Vector2f vec1, sf::Vector2f vec2);
	float CrossProduct(sf::Vector2f vec1, sf::Vector2f vec2);


	sf::Vector2f GetNormal(sf::Vector2f line);
	sf::Vector2f Reflection(sf::Vector2f incomingVec, sf::Vector2f normal);

	sf::Vector2f Normalise(sf::Vector2f vec);


}