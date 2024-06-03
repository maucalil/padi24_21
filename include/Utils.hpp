#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

class Utils
{
public:
	static sf::Vector2f NormalizeVector(sf::Vector2f vector);
	static float GetAngle(sf::Vector2f dir);
};

#endif