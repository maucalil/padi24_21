#include "System/Utils.hpp"

float Utils::GetVectorModule(sf::Vector2f vector)
{
  return sqrtf(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f Utils::NormalizeVector(sf::Vector2f vector)
{
  float mod = GetVectorModule(vector);

	sf::Vector2f normalizedVector;

	normalizedVector.x = vector.x / mod;
	normalizedVector.y = vector.y / mod;

	return normalizedVector;
}

float Utils::GetAngle(sf::Vector2f dir)
{
  return atan2f(dir.y, dir.x) * 180 / M_PI;
}