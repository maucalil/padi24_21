#include "Utils.hpp"

#include <cmath>

sf::Vector2f Utils::NormalizeVector(sf::Vector2f vector)
{
  float m = std::sqrt(vector.x * vector.x + vector.y * vector.y);

	sf::Vector2f normalizedVector;

	normalizedVector.x = vector.x / m;
	normalizedVector.y = vector.y / m;

	return normalizedVector;
  return sf::Vector2f();
}

float Utils::GetAngle(sf::Vector2f dir)
{
  return atan(dir.y / dir.x) * 180 / M_PI;
}
