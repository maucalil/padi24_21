#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

class Utils
{
public:

	static float GetVectorModule(sf::Vector2f vector);
	static sf::Vector2f NormalizeVector(sf::Vector2f vector);
	static float GetAngle(sf::Vector2f dir);
	static std::string to_string_with_precision(float value, int precision = 2);
};

#endif